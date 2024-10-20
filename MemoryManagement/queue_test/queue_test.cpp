#include "../../Tools/Testing/test_helper.hpp"
#include "../queue.hpp"


#if defined(QT_TESTLIB_LIB)
#include <QCoreApplication>
#include <QtTest/QtTest>
#else
#include "gtest/gtest.h"
#endif

#if defined(QT_TESTLIB_LIB)
class testQueue : public QObject
{
  Q_OBJECT

private slots:
  void testFifoEnqueueDequeue();
  void testLifoPushPop();
  void testFifoOverflow();
  void testLifoOverflow();
  void testConcurrentFifoOperations();
  void testConcurrentLifoOperations();
};
#endif

TEST_CASE(testQueue, testFifoEnqueueDequeue)
{
  const uint16_t                  QUEUE_SIZE = 10;
  MEM::fifoQueue<int, QUEUE_SIZE> fifoQueue;

  // Enqueue elements
  for (int i = 0; i < QUEUE_SIZE; ++i)
  {
    fifoQueue.push(i);
  }

  // Dequeue and verify elements
  for (int i = 0; i < QUEUE_SIZE; ++i)
  {
    int value;
    QCOMPARE(fifoQueue.pop(value), true);
    QCOMPARE(value, i); // FIFO behavior
  }

  // Ensure the queue is empty after dequeuing all elements
  QVERIFY(fifoQueue.isEmpty());
}

TEST_CASE(testQueue, testLifoPushPop)
{
  const uint16_t                  QUEUE_SIZE = 10;
  MEM::lifoQueue<int, QUEUE_SIZE> lifoQueue;

  // Push elements
  for (int i = 0; i < QUEUE_SIZE; ++i)
  {
    lifoQueue.push(i);
  }

  // Pop and verify elements (should pop in reverse order of push)
  for (int i = QUEUE_SIZE - 1; i >= 0; --i)
  {
    int value;
    QCOMPARE(lifoQueue.pop(value), true);
    QCOMPARE(value, i); // LIFO behavior
  }

  // Ensure the stack is empty after popping all elements
  QVERIFY(lifoQueue.isEmpty());
}

TEST_CASE(testQueue, testFifoOverflow)
{
  const uint16_t                  QUEUE_SIZE = 5;
  MEM::fifoQueue<int, QUEUE_SIZE> fifoQueue;

  // Fill the queue
  for (int i = 0; i < QUEUE_SIZE; ++i)
  {
    fifoQueue.push(i);
  }

  // Adding one more element to test overflow (overwrites oldest)
  fifoQueue.push(99);

  // Dequeue all elements and verify (oldest should be overwritten)
  int value;
  for (int i = 1; i < QUEUE_SIZE; ++i)
  {
    QCOMPARE(fifoQueue.pop(value), true);
    QCOMPARE(value, i); // The first element (0) should be overwritten
  }
  QCOMPARE(fifoQueue.pop(value), true);
  QCOMPARE(value, 99);
}

TEST_CASE(testQueue, testLifoOverflow)
{
  const uint16_t                  QUEUE_SIZE = 5;
  MEM::lifoQueue<int, QUEUE_SIZE> lifoQueue;

  // Fill the stack
  for (int i = 0; i < QUEUE_SIZE; ++i)
  {
    bool pushSuccess = lifoQueue.push(i);
    QCOMPARE(pushSuccess, true); // Ensure each push succeeds
  }

  // Attempt to push another element to test overflow (should fail)
  bool overflowPush = lifoQueue.push(99);
  QCOMPARE(overflowPush, false); // Push should fail since the stack is full

  // Pop and verify elements (should be in LIFO order: 4, 3, 2, 1, 0)
  int value;

  for (int expected = QUEUE_SIZE - 1; expected >= 0; --expected)
  {
    bool popSuccess = lifoQueue.pop(value);
    QCOMPARE(popSuccess, true); // Each pop should succeed
    QCOMPARE(value, expected);  // Verify the popped value
  }

  // Attempt to pop from an empty stack (should fail)
  bool emptyPop = lifoQueue.pop(value);
  QCOMPARE(emptyPop, false); // Pop should fail since the stack is empty

  // Optionally, verify that the stack is indeed empty
  QCOMPARE(lifoQueue.isEmpty(), true);
}

TEST_CASE(testQueue, testConcurrentFifoOperations)
{
  const uint16_t                  QUEUE_SIZE = 100;
  MEM::fifoQueue<int, QUEUE_SIZE> fifoQueue;

  const size_t NUM_THREADS           = 10;
  const size_t OPERATIONS_PER_THREAD = 50;

  std::vector<std::thread> threads;
  std::mutex               queueMutex;

  auto fifoOperation = [&](size_t threadIndex)
  {
    for (size_t i = 0; i < OPERATIONS_PER_THREAD; ++i)
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      fifoQueue.push(static_cast<int>(threadIndex * 100 + i));
    }
  };

  // Start multiple threads
  for (size_t i = 0; i < NUM_THREADS; ++i)
  {
    threads.emplace_back(fifoOperation, i);
  }

  // Wait for all threads to finish
  for (auto& t : threads)
  {
    t.join();
  }

  // Check if the queue is not empty
  QVERIFY(!fifoQueue.isEmpty());
}

TEST_CASE(testQueue, testConcurrentLifoOperations)
{
  const uint16_t                  QUEUE_SIZE = 100;
  MEM::lifoQueue<int, QUEUE_SIZE> lifoQueue;

  const size_t NUM_THREADS           = 10;
  const size_t OPERATIONS_PER_THREAD = 50;

  std::vector<std::thread> threads;
  std::mutex               queueMutex;

  auto lifoOperation = [&](size_t threadIndex)
  {
    for (size_t i = 0; i < OPERATIONS_PER_THREAD; ++i)
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      lifoQueue.push(static_cast<int>(threadIndex * 100 + i));
    }
  };

  // Start multiple threads
  for (size_t i = 0; i < NUM_THREADS; ++i)
  {
    threads.emplace_back(lifoOperation, i);
  }

  // Wait for all threads to finish
  for (auto& t : threads)
  {
    t.join();
  }

  // Check if the stack is not empty
  QVERIFY(!lifoQueue.isEmpty());
}

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(testQueue)
#include "queue_test.moc"
#endif
