#include "../../Tools/Testing/test_helper.hpp"
#include "../ring_buffer.hpp"


#if defined(QT_TESTLIB_LIB)
#include <QCoreApplication>
#include <QtTest/QtTest>
#else
#include "gtest/gtest.h"
#endif

#if defined(QT_TESTLIB_LIB)
class testRingBuffer : public QObject
{
  Q_OBJECT

private slots:
  void testRingBufferWrite();
  void testRingBufferRead();
  void testRingBufferWriteMultiple();
  void testRingBufferReadMultiple();
  void testRingBufferPeek();
  void testRingBufferIndexOperator();
  void testRingBufferReset();
  void testRingBufferOverwrite();
  void testRingBufferDifferentTypes();
};
#endif

TEST_CASE(testRingBuffer, testRingBufferWrite)
{
  // Instantiate the ringBuffer class with buffer size to hold 5 integers
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;

  // Write elements to the buffer and check if write was successful
  QVERIFY(myRingBuffer.write(1));
  QVERIFY(myRingBuffer.write(2));
  QVERIFY(myRingBuffer.write(3));
  QVERIFY(myRingBuffer.write(4));
  QVERIFY(myRingBuffer.write(5));

  // Check if the buffer is full before attempting to write more data
  QVERIFY(myRingBuffer.isFull());

  // Try to write an element to a full buffer
  QVERIFY(!myRingBuffer.write(6));
}

TEST_CASE(testRingBuffer, testRingBufferRead)
{
  // Instantiate the ringBuffer class with buffer size to hold 5 integers
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);
  myRingBuffer.write(4);
  myRingBuffer.write(5);

  // Read elements from the buffer and check if read was successful
  int value;
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 1);
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 2);
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 3);
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 4);
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 5);

  // Try to read an element from an empty buffer
  QVERIFY(!myRingBuffer.read(value));
  QVERIFY(myRingBuffer.isEmpty());
}

TEST_CASE(testRingBuffer, testRingBufferWriteMultiple)
{
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;
  int                                   data[3] = { 1, 2, 3 };

  // Write multiple elements to the buffer and check if write was successful
  std::size_t itemsWritten = myRingBuffer.write(data, 3);
  QCOMPARE(static_cast<int>(itemsWritten), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.capacity()), 5);
  QCOMPARE(static_cast<int>(myRingBuffer.count()), 3);

  // Check if the buffer is full before attempting to write more data
  QVERIFY(!myRingBuffer.isFull());

  // Write more elements to fill the buffer
  itemsWritten = myRingBuffer.write(data, 2);
  QCOMPARE(static_cast<int>(itemsWritten), 2);

  QVERIFY(myRingBuffer.isFull());
}

TEST_CASE(testRingBuffer, testRingBufferReadMultiple)
{
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;
  int                                   data[5] = { 1, 2, 3, 4, 5 };

  // Write elements to the buffer
  std::size_t itemsWritten = myRingBuffer.write(data, 5);
  QCOMPARE(static_cast<int>(itemsWritten), 5);

  // Read multiple elements from the buffer and check if read was successful
  int         values[3];
  std::size_t itemsRead = myRingBuffer.read(values, 3);
  QCOMPARE(static_cast<int>(itemsRead), 3);
  QCOMPARE(values[0], 1);
  QCOMPARE(values[1], 2);
  QCOMPARE(values[2], 3);
  QCOMPARE(static_cast<int>(myRingBuffer.capacity()), 5);
  QCOMPARE(static_cast<int>(myRingBuffer.count()), 2);

  // Try to read more elements from the buffer than are available
  itemsRead = myRingBuffer.read(values, 3);
  QCOMPARE(static_cast<int>(itemsRead), 2);
  QCOMPARE(values[0], 4);
  QCOMPARE(values[1], 5);
}

TEST_CASE(testRingBuffer, testRingBufferPeek)
{
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);
  myRingBuffer.write(4);
  myRingBuffer.write(5);

  // Peek elements from the buffer and check if peek was successful
  int value;
  QVERIFY(myRingBuffer.peek(value, 0));
  QCOMPARE(value, 1);
  QVERIFY(myRingBuffer.peek(value, 1));
  QCOMPARE(value, 2);
  QVERIFY(myRingBuffer.peek(value, 2));
  QCOMPARE(value, 3);
  QVERIFY(myRingBuffer.peek(value, 3));
  QCOMPARE(value, 4);
  QVERIFY(myRingBuffer.peek(value, 4));
  QCOMPARE(value, 5);
}

TEST_CASE(testRingBuffer, testRingBufferIndexOperator)
{
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;
  int                                   data[5] = { 1, 2, 3, 4, 5 };

  // Write elements to the buffer
  std::size_t itemsWritten = myRingBuffer.write(data, 5);
  QCOMPARE(static_cast<int>(itemsWritten), 5);

  // Check if the operator[] returns the expected values for the given indices
  QCOMPARE(myRingBuffer[0], 1);
  QCOMPARE(myRingBuffer[2], 3);
  QCOMPARE(myRingBuffer[4], 5);
}

TEST_CASE(testRingBuffer, testRingBufferReset)
{
  MEM::ringBuffer<int, 5 * sizeof(int)> myRingBuffer;

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);

  // Verify that the buffer is not empty
  QVERIFY(!myRingBuffer.isEmpty());

  // Reset the buffer
  myRingBuffer.reset();

  // Verify that the buffer is now empty
  QVERIFY(myRingBuffer.isEmpty());
}

TEST_CASE(testRingBuffer, testRingBufferOverwrite)
{
  MEM::ringBuffer<int, 3 * sizeof(int)> myRingBuffer(MEM::RINGBUFFER_ALLOW_OVERWRITE);

  // Write more elements than the buffer capacity
  QVERIFY(myRingBuffer.write(1));
  QVERIFY(myRingBuffer.write(2));
  QVERIFY(myRingBuffer.write(3));
  QVERIFY(myRingBuffer.isFull());
  QVERIFY(myRingBuffer.write(4)); // Overwrites the oldest data (1)
  QVERIFY(myRingBuffer.write(5)); // Overwrites the next oldest data (2)

  // Verify that the buffer is full
  QVERIFY(myRingBuffer.isFull());

  // Verify the content of the buffer
  QCOMPARE(myRingBuffer[0], 3); // Oldest element
  QCOMPARE(myRingBuffer[1], 4);
  QCOMPARE(myRingBuffer[2], 5); // Newest element

  // Read an element to make space
  int value;
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 3);
  QVERIFY(!myRingBuffer.isFull());
  QCOMPARE(static_cast<int>(myRingBuffer.capacity()), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.count()), 2);

  // Write another element to the buffer
  QVERIFY(myRingBuffer.write(6));

  // Verify that the buffer is full again and that the correct elements are in the buffer
  QVERIFY(myRingBuffer.isFull());
  QCOMPARE(static_cast<int>(myRingBuffer.capacity()), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.count()), 3);
  QCOMPARE(myRingBuffer[0], 4); // Oldest element
  QCOMPARE(myRingBuffer[1], 5);
  QCOMPARE(myRingBuffer[2], 6); // Newest element
}

TEST_CASE(testRingBuffer, testRingBufferDifferentTypes)
{
  // Define a struct
  struct myStruct
  {
    int foo;
    int bar;
  };

  // Define an enum
  enum myEnum
  {
    foo,
    bar
  };

  // Define a union to store an array of characters
  union myUnion
  {
    uint8_t string[3];
  };

  // Instantiate the ring buffer for each data type
  MEM::ringBuffer<myStruct, 3 * sizeof(myStruct)> structRingBuffer;
  MEM::ringBuffer<myEnum, 3 * sizeof(myEnum)>     enumRingBuffer;
  MEM::ringBuffer<myUnion, 3 * sizeof(myUnion)>   charArrayRingBuffer;

  // Write values to the struct ring buffer
  myStruct structValue1 = { 1, 2 };
  myStruct structValue2 = { 3, 4 };
  QVERIFY(structRingBuffer.write(structValue1));
  QVERIFY(structRingBuffer.write(structValue2));
  QCOMPARE(static_cast<int>(structRingBuffer.capacity()), 3);
  QCOMPARE(static_cast<int>(structRingBuffer.count()), 2);
  QCOMPARE(structRingBuffer[0].foo, 1);
  QCOMPARE(structRingBuffer[0].bar, 2);
  QCOMPARE(structRingBuffer[1].foo, 3);
  QCOMPARE(structRingBuffer[1].bar, 4);

  // Write values to the enum ring buffer
  QVERIFY(enumRingBuffer.write(foo));
  QVERIFY(enumRingBuffer.write(bar));
  QCOMPARE(static_cast<int>(enumRingBuffer.capacity()), 3);
  QCOMPARE(static_cast<int>(enumRingBuffer.count()), 2);
  QCOMPARE(enumRingBuffer[0], foo);
  QCOMPARE(enumRingBuffer[1], bar);

  // Write values to the character array ring buffer
  myUnion charArrayValue1 = { { 'a', 'b', 'c' } };
  myUnion charArrayValue2 = { { 'd', 'e', 'f' } };
  QVERIFY(charArrayRingBuffer.write(charArrayValue1));
  QVERIFY(charArrayRingBuffer.write(charArrayValue2));
  QCOMPARE(static_cast<int>(charArrayRingBuffer.capacity()), 3);
  QCOMPARE(static_cast<int>(charArrayRingBuffer.count()), 2);
  QCOMPARE(static_cast<char>(charArrayRingBuffer[0].string[0]), 'a');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[0].string[1]), 'b');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[0].string[2]), 'c');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[1].string[0]), 'd');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[1].string[1]), 'e');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[1].string[2]), 'f');
}

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(testRingBuffer)
#include "debug/ring_buffer_test.moc"
#endif
