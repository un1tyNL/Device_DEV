#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <mutex>
#include <thread>
#include <type_traits>

namespace MEM
{
  /**
   * @brief Enumeration for memory pool errors.
   */
  enum class memoryPoolErrors
  {
    SUCCESS,
    INVALID_HANDLE,
    INVALID_SIZE,
    ALLOCATION_FAILED,
    DOUBLE_FREE_ATTEMPT,
    HANDLE_OVERFLOW,
    HANDLE_TABLE_FULL,
    ALIGNMENT_ERROR,
    UNKNOWN_ERROR
  };

  /**
   * @brief Template class for managing a memory pool of a fixed size using handles.
   * @tparam poolSize Size of the memory pool in bytes.
   * @tparam maxHandles Maximum number of handles that can be allocated.
   */
  template <size_t poolSize, size_t maxHandles = 1024>
  class memoryPool
  {
  public:
    using Handle = size_t;

  private:
    /**
     * @brief Structure representing a memory block within the pool.
     */
    struct memoryBlock
    {
      size_t       size;    //!< Size of the block (excluding the header).
      bool         is_free; //!< Flag indicating if the block is free.
      memoryBlock* next;    //!< Pointer to the next block.
      memoryBlock* prev;    //!< Pointer to the previous block.
      Handle       handle;  //!< Handle associated with this block.
    };

    // Statically allocated memory pool.
    alignas(std::max_align_t) uint8_t pool[poolSize];

    // Head of the memory block linked list.
    memoryBlock* head;

    // Mutex to protect the memory pool.
    std::mutex pool_mutex;

    // Handle management
    memoryBlock* handleTable[maxHandles]; //!< Direct mapping from handle to memory block.
    size_t       freeHandles[maxHandles]; //!< Stack of free handle indices.
    size_t       freeHandleCount;

    // Helper constants for alignment
    static constexpr size_t memoryBlockAlignedSize
      = (sizeof(memoryBlock) + alignof(std::max_align_t) - 1) & ~(alignof(std::max_align_t) - 1);

    // Minimal block size to prevent creating unusable small blocks
    static constexpr size_t minimalBlockSize = memoryBlockAlignedSize + alignof(std::max_align_t);

  public:
    /**
     * @brief Constructor for the memoryPool class.
     */
    memoryPool()
    {
      static_assert(poolSize > memoryBlockAlignedSize + minimalBlockSize, "Pool size too small.");

      // Initialize the head block
      head          = reinterpret_cast<memoryBlock*>(pool);
      head->size    = poolSize - memoryBlockAlignedSize;
      head->is_free = true;
      head->next    = nullptr;
      head->prev    = nullptr;
      head->handle  = 0;

      // Initialize handle management
      freeHandleCount = maxHandles;
      for (size_t i = 0; i < maxHandles; ++i)
      {
        freeHandles[i] = maxHandles - i - 1; // Initialize free handles stack
        handleTable[i] = nullptr;
      }
    }

    /**
     * @brief Allocates a memory block of the specified size and returns a handle.
     * @param size Size of the memory block to allocate.
     * @param outHandle Reference to a handle variable to store the allocated handle.
     * @return memoryPoolErrors value indicating the result of the operation.
     */
    memoryPoolErrors alloc(size_t size, Handle& outHandle)
    {
      std::lock_guard<std::mutex> lock(pool_mutex);

      if (size == 0 || size > poolSize - memoryBlockAlignedSize)
      {
        return memoryPoolErrors::INVALID_SIZE;
      }

      // Ensure alignment for the data
      size = (size + alignof(std::max_align_t) - 1) & ~(alignof(std::max_align_t) - 1);

      memoryBlock* current = head;
      while (current != nullptr)
      {
        if (current->is_free && current->size >= size)
        {
          size_t totalAllocSize = size + memoryBlockAlignedSize;

          // Check if we can split the block
          if (current->size >= totalAllocSize + minimalBlockSize)
          {
            // Split the block
            memoryBlock* new_block = reinterpret_cast<memoryBlock*>(reinterpret_cast<uint8_t*>(current) + totalAllocSize);

            new_block->size    = current->size - totalAllocSize;
            new_block->is_free = true;
            new_block->next    = current->next;
            new_block->prev    = current;
            new_block->handle  = 0;

            if (current->next)
            {
              current->next->prev = new_block;
            }

            current->next = new_block;
            current->size = size;
          }

          current->is_free = false;

          // Assign a new handle
          if (freeHandleCount == 0)
          {
            return memoryPoolErrors::HANDLE_TABLE_FULL;
          }

          Handle handle       = freeHandles[--freeHandleCount];
          current->handle     = handle;
          handleTable[handle] = current;
          outHandle           = handle;

          return memoryPoolErrors::SUCCESS;
        }
        current = current->next;
      }

      // No suitable block found
      return memoryPoolErrors::ALLOCATION_FAILED;
    }

    /**
     * @brief Frees a previously allocated memory block using its handle.
     * @param handle The handle of the memory block to free.
     * @return memoryPoolErrors value indicating the result of the operation.
     */
    memoryPoolErrors free(Handle handle)
    {
      std::lock_guard<std::mutex> lock(pool_mutex);

      if (handle >= maxHandles || handleTable[handle] == nullptr)
      {
        return memoryPoolErrors::INVALID_HANDLE;
      }

      memoryBlock* block = handleTable[handle];

      if (block->is_free)
      {
        return memoryPoolErrors::DOUBLE_FREE_ATTEMPT;
      }

      block->is_free = true;
      block->handle  = 0;

      // Remove the handle from the handle table
      handleTable[handle]            = nullptr;
      freeHandles[freeHandleCount++] = handle;

      // Coalesce with next block if it's free
      if (block->next && block->next->is_free)
      {
        block->size += memoryBlockAlignedSize + block->next->size;
        block->next = block->next->next;
        if (block->next)
        {
          block->next->prev = block;
        }
      }

      // Coalesce with previous block if it's free
      if (block->prev && block->prev->is_free)
      {
        block->prev->size += memoryBlockAlignedSize + block->size;
        block->prev->next = block->next;
        if (block->next)
        {
          block->next->prev = block->prev;
        }
        block = block->prev;
      }

      return memoryPoolErrors::SUCCESS;
    }

    /**
     * @brief Retrieves a pointer to the memory block associated with the given handle.
     * @param handle The handle of the memory block.
     * @return Pointer to the memory block, or nullptr if the handle is invalid.
     */
    void* getPointer(Handle handle)
    {
      std::lock_guard<std::mutex> lock(pool_mutex);

      if (handle >= maxHandles || handleTable[handle] == nullptr)
      {
        return nullptr;
      }

      memoryBlock* block = handleTable[handle];
      return reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(block) + memoryBlockAlignedSize);
    }

    /**
     * @brief Defragments the memory pool by moving allocated blocks and updating handles.
     */
    void defragment()
    {
      std::lock_guard<std::mutex> lock(pool_mutex);

      // Temporary arrays for allocated blocks
      Handle allocatedHandles[maxHandles];
      size_t allocatedSizes[maxHandles];
      void*  oldPointers[maxHandles];
      size_t allocatedCount = 0;

      // Collect allocated blocks and their sizes
      memoryBlock* current = head;
      while (current != nullptr)
      {
        if (!current->is_free)
        {
          allocatedHandles[allocatedCount] = current->handle;
          allocatedSizes[allocatedCount]   = current->size;
          oldPointers[allocatedCount]      = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(current) + memoryBlockAlignedSize);
          ++allocatedCount;
        }
        current = current->next;
      }

      // Reset the memory pool
      head          = reinterpret_cast<memoryBlock*>(pool);
      head->size    = poolSize - memoryBlockAlignedSize;
      head->is_free = true;
      head->next    = nullptr;
      head->prev    = nullptr;
      head->handle  = 0;

      memoryBlock* prevBlock  = nullptr;
      uint8_t*     currentPtr = pool;

      // Reallocate blocks sequentially
      for (size_t i = 0; i < allocatedCount; ++i)
      {
        Handle handle = allocatedHandles[i];
        size_t size   = allocatedSizes[i];

        // Ensure alignment for the current pointer
        currentPtr = reinterpret_cast<uint8_t*>((reinterpret_cast<size_t>(currentPtr) + alignof(std::max_align_t) - 1)
                                                & ~(alignof(std::max_align_t) - 1));

        // Allocate new block
        memoryBlock* newBlock = reinterpret_cast<memoryBlock*>(currentPtr);
        newBlock->size        = size;
        newBlock->is_free     = false;
        newBlock->prev        = prevBlock;
        newBlock->next        = nullptr;
        newBlock->handle      = handle;

        if (prevBlock)
        {
          prevBlock->next = newBlock;
        }
        else
        {
          head = newBlock; // This is the first block
        }

        // Update the handle table
        handleTable[handle] = newBlock;

        prevBlock  = newBlock;
        currentPtr = reinterpret_cast<uint8_t*>(newBlock) + memoryBlockAlignedSize + size;
      }

      // Create a free block with the remaining memory
      if (currentPtr < pool + poolSize - minimalBlockSize)
      {
        // Ensure alignment for the free block
        currentPtr = reinterpret_cast<uint8_t*>((reinterpret_cast<size_t>(currentPtr) + alignof(std::max_align_t) - 1)
                                                & ~(alignof(std::max_align_t) - 1));

        if (currentPtr < pool + poolSize - minimalBlockSize)
        {
          memoryBlock* freeBlock = reinterpret_cast<memoryBlock*>(currentPtr);

          freeBlock->size    = (pool + poolSize) - (reinterpret_cast<uint8_t*>(freeBlock) + memoryBlockAlignedSize);
          freeBlock->is_free = true;
          freeBlock->prev    = prevBlock;
          freeBlock->next    = nullptr;
          freeBlock->handle  = 0;

          if (prevBlock)
          {
            prevBlock->next = freeBlock;
          }
          else
          {
            head = freeBlock; // If there were no allocated blocks
          }
        }
      }

      // Copy data from old locations to new locations
      for (size_t i = 0; i < allocatedCount; ++i)
      {
        Handle handle = allocatedHandles[i];
        size_t size   = allocatedSizes[i];
        void*  oldPtr = oldPointers[i];

        memoryBlock* newBlock = handleTable[handle];

        if (newBlock)
        {
          void* newPtr = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(newBlock) + memoryBlockAlignedSize);
          if (oldPtr && newPtr)
          {
            std::memmove(newPtr, oldPtr, size);
          }
        }
      }
    }

    /**
     * @brief Returns the maximum size that can be allocated in a single allocation request.
     * @return The maximum allocatable memory size in bytes.
     */
    size_t getMaxAllocatableSize()
    {
      std::lock_guard<std::mutex> lock(pool_mutex);

      size_t       maxAllocatable = 0;
      memoryBlock* current        = head;
      while (current != nullptr)
      {
        if (current->is_free)
        {
          size_t allocatableSize = current->size;

          // Adjust for minimal block size if splitting is possible
          if (current->size >= minimalBlockSize + memoryBlockAlignedSize)
          {
            allocatableSize -= memoryBlockAlignedSize;
          }

          // Ensure alignment
          allocatableSize &= ~(alignof(std::max_align_t) - 1);

          if (allocatableSize > maxAllocatable)
          {
            maxAllocatable = allocatableSize;
          }
        }
        current = current->next;
      }

      return maxAllocatable;
    }

    /**
     * @brief Retrieves the total free memory available in the pool.
     * @return The total free memory in bytes.
     */
    size_t getTotalFreeMemory()
    {
      std::lock_guard<std::mutex> lock(pool_mutex);

      size_t       totalFree = 0;
      memoryBlock* current   = head;
      while (current != nullptr)
      {
        if (current->is_free)
        {
          totalFree += current->size;
        }
        current = current->next;
      }
      return totalFree;
    }

    /**
     * @brief Returns the size of the memory block header.
     * @return The size in bytes.
     */
    static constexpr size_t getMemoryBlockHeaderSize()
    {
      return memoryBlockAlignedSize;
    }

    /**
     * @brief Returns the minimal block size enforced by the allocator.
     * @return The minimal block size in bytes.
     */
    static constexpr size_t getMinimalBlockSize()
    {
      return minimalBlockSize;
    }
  };

} // namespace MEM
