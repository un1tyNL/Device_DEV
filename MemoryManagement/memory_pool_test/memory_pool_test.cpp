#include "memory_pool.hpp"
#include "../../Tools/Testing/test_helper.hpp"

#if defined(QT_TESTLIB_LIB)
#include <QCoreApplication>
#include <QtTest/QtTest>
#else
#include "gtest/gtest.h"
#endif

#include <thread>
#include <vector>
#include <mutex>
#include <cstring>
#include <cstdint>
#include <limits>

#if defined(QT_TESTLIB_LIB)
class testMemoryPool : public QObject
{
    Q_OBJECT

private slots:
    void testAllocation();
    void testDeallocation();
    void testAllocationFailure();
    void testDefragmentation();
    void testConcurrentAllocations();
    void testGetMaxAllocatableSize();
    void testGetTotalFreeMemory();
    void testZeroByteAllocation();
    void testInvalidSizeAllocation();
    void testInvalidHandleFree();
    void testHandleTableFull256();
    void testHandleTableFull512();
    void testHandleTableFull1024();
    void testHandleTableFull2048();
    void testHandleTableFull4096();
    void testBlockCoalescing();
    void testAlignmentConstraints();
    void testMinimalBlockSizeEnforcement();
};
#endif

// The TEST_CASE macro is assumed to be defined in "../../Tools/Testing/test_helper.hpp" to handle both QtTest and Google Test frameworks.

TEST_CASE(testMemoryPool, testAllocation)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle1, handle2, handle3;

    // Allocate several blocks of varying sizes
    auto result1 = memPool.alloc(100, handle1);
    QCOMPARE(result1, MEM::memoryPoolErrors::SUCCESS);
    QVERIFY(handle1 != std::numeric_limits<MEM::memoryPool<POOL_SIZE>::Handle>::max());

    auto result2 = memPool.alloc(200, handle2);
    QCOMPARE(result2, MEM::memoryPoolErrors::SUCCESS);
    QVERIFY(handle2 != std::numeric_limits<MEM::memoryPool<POOL_SIZE>::Handle>::max());
    QVERIFY(handle2 != handle1);

    auto result3 = memPool.alloc(300, handle3);
    QCOMPARE(result3, MEM::memoryPoolErrors::SUCCESS);
    QVERIFY(handle3 != std::numeric_limits<MEM::memoryPool<POOL_SIZE>::Handle>::max());
    QVERIFY(handle3 != handle1);
    QVERIFY(handle3 != handle2);

    // Ensure that the handles are valid
    void* ptr1 = memPool.getPointer(handle1);
    void* ptr2 = memPool.getPointer(handle2);
    void* ptr3 = memPool.getPointer(handle3);
    QVERIFY(ptr1 != nullptr);
    QVERIFY(ptr2 != nullptr);
    QVERIFY(ptr3 != nullptr);
    QVERIFY(ptr1 != ptr2);
    QVERIFY(ptr2 != ptr3);
    QVERIFY(ptr1 != ptr3);

    // Check alignment
    QVERIFY(reinterpret_cast<size_t>(ptr1) % alignof(std::max_align_t) == 0);
    QVERIFY(reinterpret_cast<size_t>(ptr2) % alignof(std::max_align_t) == 0);
    QVERIFY(reinterpret_cast<size_t>(ptr3) % alignof(std::max_align_t) == 0);

    // Optionally, write data to the allocated memory and verify it
    memset(ptr1, 0xAA, 100);
    memset(ptr2, 0xBB, 200);
    memset(ptr3, 0xCC, 300);

    // Verify the data
    for (size_t i = 0; i < 100; ++i)
    {
        QCOMPARE(static_cast<uint8_t*>(ptr1)[i], 0xAA);
    }
    for (size_t i = 0; i < 200; ++i)
    {
        QCOMPARE(static_cast<uint8_t*>(ptr2)[i], 0xBB);
    }
    for (size_t i = 0; i < 300; ++i)
    {
        QCOMPARE(static_cast<uint8_t*>(ptr3)[i], 0xCC);
    }
}

TEST_CASE(testMemoryPool, testDeallocation)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle1, handle2;

    // Allocate blocks
    auto result1 = memPool.alloc(400, handle1);
    QCOMPARE(result1, MEM::memoryPoolErrors::SUCCESS);
    QVERIFY(handle1 != std::numeric_limits<MEM::memoryPool<POOL_SIZE>::Handle>::max());

    auto result2 = memPool.alloc(400, handle2);
    QCOMPARE(result2, MEM::memoryPoolErrors::SUCCESS);
    QVERIFY(handle2 != std::numeric_limits<MEM::memoryPool<POOL_SIZE>::Handle>::max());
    QVERIFY(handle2 != handle1);

    // Free the first block
    auto freeResult1 = memPool.free(handle1);
    QCOMPARE(freeResult1, MEM::memoryPoolErrors::SUCCESS);

    // Ensure that the block is no longer accessible
    void* ptr1 = memPool.getPointer(handle1);
    QCOMPARE(ptr1, nullptr);

    // Free the second block
    auto freeResult2 = memPool.free(handle2);
    QCOMPARE(freeResult2, MEM::memoryPoolErrors::SUCCESS);

    // Ensure that the block is no longer accessible
    void* ptr2 = memPool.getPointer(handle2);
    QCOMPARE(ptr2, nullptr);

    // Attempt to free the same handle again (should fail)
    auto doubleFreeResult = memPool.free(handle1);
    QCOMPARE(doubleFreeResult, MEM::memoryPoolErrors::INVALID_HANDLE);
}

TEST_CASE(testMemoryPool, testAllocationFailure)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle;

    // Attempt to allocate more memory than available
    auto result = memPool.alloc(POOL_SIZE, handle);
    QCOMPARE(result, MEM::memoryPoolErrors::INVALID_SIZE);

    // Fill up the memory pool
    std::vector<MEM::memoryPool<POOL_SIZE>::Handle> handles;
    size_t totalAllocated = 0;
    while (true)
    {
        auto allocResult = memPool.alloc(100, handle);
        if (allocResult != MEM::memoryPoolErrors::SUCCESS)
        {
            QCOMPARE(allocResult, MEM::memoryPoolErrors::ALLOCATION_FAILED);
            break;
        }
        handles.push_back(handle);
        totalAllocated += 100;
    }

    // Ensure that the total allocated memory does not exceed the pool size
    QVERIFY(totalAllocated <= POOL_SIZE);

    // Clean up
    for (auto h : handles)
    {
        memPool.free(h);
    }
}

TEST_CASE(testMemoryPool, testDefragmentation)
{
    const size_t POOL_SIZE = 2048;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle1, handle2, handle3, handle4;

    // Allocate blocks
    memPool.alloc(400, handle1);
    memPool.alloc(400, handle2);
    memPool.alloc(400, handle3);

    // Free some blocks to create fragmentation
    memPool.free(handle2);

    // Attempt to allocate a large block (should fail due to fragmentation)
    MEM::memoryPool<POOL_SIZE>::Handle handleLarge;
    auto result = memPool.alloc(800, handleLarge);
    QCOMPARE(result, MEM::memoryPoolErrors::ALLOCATION_FAILED);

    // Defragment the memory pool
    memPool.defragment();

    // Now allocation should succeed
    result = memPool.alloc(800, handleLarge);
    QCOMPARE(result, MEM::memoryPoolErrors::SUCCESS);

    // Clean up
    memPool.free(handle1);
    memPool.free(handle3);
    memPool.free(handleLarge);
}

TEST_CASE(testMemoryPool, testConcurrentAllocations)
{
    const size_t POOL_SIZE = 4096;
    MEM::memoryPool<POOL_SIZE> memPool;

    const size_t NUM_THREADS = 10;
    const size_t ALLOCATIONS_PER_THREAD = 50;

    std::vector<std::thread> threads;
    std::mutex handleMutex;
    std::vector<MEM::memoryPool<POOL_SIZE>::Handle> handles;

    auto allocateMemory = [&](size_t threadIndex)
    {
        for (size_t i = 0; i < ALLOCATIONS_PER_THREAD; ++i)
        {
            MEM::memoryPool<POOL_SIZE>::Handle handle;
            size_t allocSize = 50 + (i % 50); // Vary allocation size

            auto result = memPool.alloc(allocSize, handle);
            if (result == MEM::memoryPoolErrors::SUCCESS)
            {
                std::lock_guard<std::mutex> lock(handleMutex);
                handles.push_back(handle);
            }
        }
    };

    // Start threads
    for (size_t i = 0; i < NUM_THREADS; ++i)
    {
        threads.emplace_back(allocateMemory, i);
    }

    // Wait for threads to finish
    for (auto& t : threads)
    {
        t.join();
    }

    // Verify total allocated memory does not exceed pool size
    size_t totalAllocated = 0;
    for (auto handle : handles)
    {
        void* ptr = memPool.getPointer(handle);
        QVERIFY(ptr != nullptr);

        // Assuming we can access the size (this would require additional accessor in the class)
        totalAllocated += 50;
    }
    QVERIFY(totalAllocated <= POOL_SIZE);

    // Clean up
    for (auto handle : handles)
    {
        memPool.free(handle);
    }
}

TEST_CASE(testMemoryPool, testGetMaxAllocatableSize)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    size_t headerSize = MEM::memoryPool<POOL_SIZE>::getMemoryBlockHeaderSize();
    size_t maxSize = memPool.getMaxAllocatableSize();
    QVERIFY(maxSize <= POOL_SIZE - headerSize);

    MEM::memoryPool<POOL_SIZE>::Handle handle;
    memPool.alloc(400, handle);

    size_t newMaxSize = memPool.getMaxAllocatableSize();
    QVERIFY(newMaxSize <= POOL_SIZE - 400 - headerSize * 2);

    // Free and check again
    memPool.free(handle);
    size_t maxSizeAfterFree = memPool.getMaxAllocatableSize();
    QCOMPARE(maxSizeAfterFree, maxSize);
}

TEST_CASE(testMemoryPool, testGetTotalFreeMemory)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    size_t headerSize = MEM::memoryPool<POOL_SIZE>::getMemoryBlockHeaderSize();
    size_t minBlockSize = MEM::memoryPool<POOL_SIZE>::getMinimalBlockSize();
    
    size_t totalFree = memPool.getTotalFreeMemory();
    QVERIFY(totalFree <= POOL_SIZE - headerSize);

    MEM::memoryPool<POOL_SIZE>::Handle handle1, handle2;
    memPool.alloc(200, handle1);
    memPool.alloc(300, handle2);

    size_t totalFreeAfterAlloc = memPool.getTotalFreeMemory();
    QVERIFY(totalFreeAfterAlloc < totalFree - 500 - 2 * headerSize);

    memPool.free(handle1);
    size_t totalFreeAfterFree = memPool.getTotalFreeMemory();
    QVERIFY(totalFreeAfterFree > totalFreeAfterAlloc);

    // After defragmentation
    memPool.defragment();
    size_t totalFreeAfterDefrag = memPool.getTotalFreeMemory();
    
    // Calculate the expected free memory
    size_t expectedFreeMemory = POOL_SIZE - 300 - 2 * headerSize;
    // Allow for some tolerance due to alignment and minimal block size
    size_t tolerance = std::max(alignof(std::max_align_t), minBlockSize);
    
    QVERIFY(totalFreeAfterDefrag >= expectedFreeMemory - tolerance);
    QVERIFY(totalFreeAfterDefrag <= expectedFreeMemory);
}

TEST_CASE(testMemoryPool, testZeroByteAllocation)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle;
    auto result = memPool.alloc(0, handle);
    QCOMPARE(result, MEM::memoryPoolErrors::INVALID_SIZE);
}

TEST_CASE(testMemoryPool, testInvalidSizeAllocation)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle;
    auto result = memPool.alloc(POOL_SIZE + 1, handle);
    QCOMPARE(result, MEM::memoryPoolErrors::INVALID_SIZE);
}

TEST_CASE(testMemoryPool, testInvalidHandleFree)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    // Attempt to free an invalid handle
    auto result = memPool.free(9999); // Assuming 9999 is out of valid range
    QCOMPARE(result, MEM::memoryPoolErrors::INVALID_HANDLE);
}

template <size_t POOL_SIZE, size_t MAX_HANDLES>
void testHandleTableFullTemplate()
{
    // Allocate the memory pool on the heap using std::unique_ptr
    using memPoolType = MEM::memoryPool<POOL_SIZE, MAX_HANDLES>;
    auto memPool = std::make_unique<memPoolType>();

    std::vector<typename memPoolType::Handle> handles;

    size_t allocationSize = 1024; // 1 KB per allocation

    // Attempt to allocate MAX_HANDLES + 1 handles to exceed the handle table limit
    for (size_t i = 0; i < MAX_HANDLES + 1; ++i)
    {
        typename memPoolType::Handle handle;
        auto result = memPool->alloc(allocationSize, handle);

        if (result == MEM::memoryPoolErrors::SUCCESS)
        {
            handles.push_back(handle);
        }
        else if (result == MEM::memoryPoolErrors::HANDLE_TABLE_FULL)
        {
            // Expected when handle table is full
            break;
        }
        else
        {
            // Handle other allocation failures if necessary
            break;
        }
    }

    // Clean up
    for (auto h : handles)
    {
        memPool->free(h);
    }
}

// Define test functions using a macro
#define DEFINE_HANDLE_TABLE_FULL_TEST(MAX_HANDLES) \
TEST_CASE(testMemoryPool, testHandleTableFull##MAX_HANDLES) \
{ \
    testHandleTableFullTemplate<1024 * 1024, MAX_HANDLES>(); \
}
DEFINE_HANDLE_TABLE_FULL_TEST(256);
DEFINE_HANDLE_TABLE_FULL_TEST(512);
DEFINE_HANDLE_TABLE_FULL_TEST(1024);
DEFINE_HANDLE_TABLE_FULL_TEST(2048);
DEFINE_HANDLE_TABLE_FULL_TEST(4096);
#undef DEFINE_HANDLE_TABLE_FULL_TEST

TEST_CASE(testMemoryPool, testBlockCoalescing)
{
    const size_t POOL_SIZE = 2048;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle1, handle2, handle3;

    // Allocate three blocks
    memPool.alloc(400, handle1);
    memPool.alloc(400, handle2);
    memPool.alloc(400, handle3);

    // Free the middle block
    memPool.free(handle2);

    // Check total free memory
    size_t totalFreeBefore = memPool.getTotalFreeMemory();

    // Free adjacent block
    memPool.free(handle3);

    // Check if blocks coalesced
    size_t totalFreeAfter = memPool.getTotalFreeMemory();
    QVERIFY(totalFreeAfter > totalFreeBefore);

    // The free blocks should have coalesced into a larger block
    size_t maxAllocatable = memPool.getMaxAllocatableSize();
    QVERIFY(maxAllocatable >= 800);
}

TEST_CASE(testMemoryPool, testAlignmentConstraints)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    MEM::memoryPool<POOL_SIZE>::Handle handle;
    memPool.alloc(50, handle);

    void* ptr = memPool.getPointer(handle);
    QVERIFY(ptr != nullptr);

    // Check alignment
    QVERIFY(reinterpret_cast<size_t>(ptr) % alignof(std::max_align_t) == 0);

    memPool.free(handle);
}

TEST_CASE(testMemoryPool, testMinimalBlockSizeEnforcement)
{
    const size_t POOL_SIZE = 1024;
    MEM::memoryPool<POOL_SIZE> memPool;

    size_t minimalBlockSize = MEM::memoryPool<POOL_SIZE>::getMinimalBlockSize();

    // Allocate a block that leaves an unusable small block
    MEM::memoryPool<POOL_SIZE>::Handle handle;
    memPool.alloc(POOL_SIZE - minimalBlockSize - memPool.getMemoryBlockHeaderSize(), handle);

    // Try to allocate a small block which should fail due to minimal block size constraint
    MEM::memoryPool<POOL_SIZE>::Handle smallHandle;
    auto result = memPool.alloc(1, smallHandle);
    QCOMPARE(result, MEM::memoryPoolErrors::ALLOCATION_FAILED);

    memPool.free(handle);
}

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(testMemoryPool)
#include "memory_pool_test.moc"
#endif
