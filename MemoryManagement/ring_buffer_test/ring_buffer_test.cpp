#include "../ring_buffer.hpp"
#include "../../Tools/Testing/test_helper.hpp"

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
  void testStaticRingBufferWrite();
  void testStaticRingBufferRead();
  void testStaticRingBufferWriteMultiple();
  void testStaticRingBufferReadMultiple();
  void testStaticRingBufferPeek();
  void testStaticRingBufferIndexOperator();
  void testStaticRingBufferReset();
  void testStaticRingBufferOverwrite();
  void testStaticBufferDifferentTypes();

  void testDynamicRingBufferWrite();
  void testDynamicRingBufferRead();
  void testDynamicRingBufferWriteMultiple();
  void testDynamicRingBufferReadMultiple();
  void testDynamicRingBufferPeek();
  void testDynamicRingBufferIndexOperator();
  void testDynamicBufferReset();
  void testDynamicRingBufferOverwrite();
};
#endif

TEST_CASE(testRingBuffer, testStaticRingBufferWrite)
{
  // Instantiate an instance of the staticRingBuffer class with that buffer
  MEM::staticRingBuffer<int, 5> myRingBuffer;

  // Write elements to the buffer and check if write was successful
  QVERIFY(myRingBuffer.write(1));
  QVERIFY(myRingBuffer.write(2));
  QVERIFY(myRingBuffer.write(3));
  QVERIFY(myRingBuffer.write(4));
  QVERIFY(myRingBuffer.write(5));

  // Check if the buffer is full before attempting to write more data
  QVERIFY(myRingBuffer.ringBufferIsFull());

  // Try to write an element to a full buffer
  QVERIFY(!myRingBuffer.write(6));
}

TEST_CASE(testRingBuffer, testStaticRingBufferRead)
{
  // Instantiate an instance of the staticRingBuffer class with that buffer
  MEM::staticRingBuffer<int, 5> myRingBuffer;

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
  QVERIFY(myRingBuffer.ringBufferIsEmpty());
}

TEST_CASE(testRingBuffer, testStaticRingBufferWriteMultiple)
{
  MEM::staticRingBuffer<int, 5> myRingBuffer;
  int                           data[3] = { 1, 2, 3 };

  // Write multiple elements to the buffer and check if write was successful
  QVERIFY(myRingBuffer.write(data, 3));
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 5);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 3);

  // Check if the buffer is full before attempting to write more data
  QVERIFY(!myRingBuffer.ringBufferIsFull());

  // Try to write more elements to a full buffer
  QVERIFY(myRingBuffer.write(data, 2));

  QVERIFY(myRingBuffer.ringBufferIsFull());
}

TEST_CASE(testRingBuffer, testStaticRingBufferReadMultiple)
{
  MEM::staticRingBuffer<int, 5> myRingBuffer;
  int                           data[5] = { 1, 2, 3, 4, 5 };

  // Write elements to the buffer
  QVERIFY(myRingBuffer.write(data, 5));

  // Read multiple elements from the buffer and check if read was successful
  int values[3];
  QCOMPARE(static_cast<int>(myRingBuffer.read(values, 3)), 3);
  QCOMPARE(values[0], 1);
  QCOMPARE(values[1], 2);
  QCOMPARE(values[2], 3);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 5);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 2);

  // Try to read more elements from the buffer than are available
  QCOMPARE(static_cast<int>(myRingBuffer.read(values, 3)), 2);
}

TEST_CASE(testRingBuffer, testStaticRingBufferPeek)
{
  // Instantiate an instance of the staticRingBuffer class with that buffer
  MEM::staticRingBuffer<int, 5> myRingBuffer;

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);
  myRingBuffer.write(4);
  myRingBuffer.write(5);

  // Peek elements from the buffer and check if peek was successful
  int value;
  myRingBuffer.peek(value, 0);
  QCOMPARE(value, 1);
  myRingBuffer.peek(value, 1);
  QCOMPARE(value, 2);
  myRingBuffer.peek(value, 2);
  QCOMPARE(value, 3);
  myRingBuffer.peek(value, 3);
  QCOMPARE(value, 4);
  myRingBuffer.peek(value, 4);
  QCOMPARE(value, 5);
}

TEST_CASE(testRingBuffer, testStaticRingBufferIndexOperator)
{
  MEM::staticRingBuffer<int, 5> myRingBuffer;
  int                           data[5] = { 1, 2, 3, 4, 5 };

  // Write elements to the buffer
  QVERIFY(myRingBuffer.write(data, 5));

  // Check if the operator[] returns the expected values for the given indices
  QCOMPARE(myRingBuffer[0], 1);
  QCOMPARE(myRingBuffer[2], 3);
  QCOMPARE(myRingBuffer[4], 5);
}

TEST_CASE(testRingBuffer, testStaticRingBufferReset)
{
  // Instantiate an instance of the staticRingBuffer class with that buffer
  MEM::staticRingBuffer<int, 5> myRingBuffer;

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);

  // Verify that the buffer is not empty
  QVERIFY(!myRingBuffer.ringBufferIsEmpty());

  // Reset the buffer
  myRingBuffer.reset();

  // Verify that the buffer is now empty
  QVERIFY(myRingBuffer.ringBufferIsEmpty());
}

TEST_CASE(testRingBuffer, testStaticRingBufferOverwrite)
{
  // Instantiate an instance of the staticRingBuffer class with that buffer
  MEM::staticRingBuffer<int, 3> myRingBuffer(MEM::RINGBUFFER_ALLOW_OVERWRITE);

  // Write more elements than the buffer capacity
  QVERIFY(myRingBuffer.write(1));
  QVERIFY(myRingBuffer.write(2));
  QVERIFY(myRingBuffer.write(3));
  QVERIFY(myRingBuffer.ringBufferIsFull());
  QVERIFY(myRingBuffer.write(4));
  QVERIFY(myRingBuffer.write(5));

  // Verify that the buffer is full
  QVERIFY(myRingBuffer.ringBufferIsFull());

  // Verify the content of the buffer
  QCOMPARE(myRingBuffer[0], 4);
  QCOMPARE(myRingBuffer[1], 5);
  QCOMPARE(myRingBuffer[2], 3);

  // Read an element to make space
  int value;
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 3);
  QVERIFY(!myRingBuffer.ringBufferIsFull());
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 2);
  QVERIFY(!myRingBuffer.ringBufferIsFull());

  // Write another element to the buffer
  QVERIFY(myRingBuffer.write(6));

  // Verify that the buffer is full again and that the correct elements are in the buffer
  QVERIFY(myRingBuffer.ringBufferIsFull());
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 3);
  QCOMPARE(myRingBuffer[0], 4);
  QCOMPARE(myRingBuffer[1], 5);
  QCOMPARE(myRingBuffer[2], 6);
}

TEST_CASE(testRingBuffer, testStaticBufferDifferentTypes)
{
  // Define a struct
  typedef struct myStruct
  {
    int foo;
    int bar;
  } myStruct_t;

  // Define an enum
  typedef enum myEnum
  {
    foo,
    bar
  } myEnum_e;

  // Define a union to store an array of characters
  typedef union myUnion
  {
    uint8_t string[3];
  } myUnion_t;

  // Define a void pointer
  typedef void *myVoid_p;

  // Instantiate the ring buffer for each data type
  MEM::staticRingBuffer<myStruct_t, 3> structRingBuffer;
  MEM::staticRingBuffer<myEnum_e, 3>   enumRingBuffer;
  MEM::staticRingBuffer<myUnion_t, 3>  charArrayRingBuffer;
  MEM::staticRingBuffer<myVoid_p, 3>   voidPtrRingBuffer;

  // Write values to the struct ring buffer
  myStruct_t structValue1 = { 1, 2 };
  myStruct_t structValue2 = { 3, 4 };
  QVERIFY(structRingBuffer.write(structValue1));
  QVERIFY(structRingBuffer.write(structValue2));
  QCOMPARE(static_cast<int>(structRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(structRingBuffer.ringBufferElementsWritten()), 2);
  QCOMPARE(structRingBuffer[0].foo, 1);
  QCOMPARE(structRingBuffer[0].bar, 2);
  QCOMPARE(structRingBuffer[1].foo, 3);
  QCOMPARE(structRingBuffer[1].bar, 4);

  // Write values to the enum ring buffer
  QVERIFY(enumRingBuffer.write(foo));
  QVERIFY(enumRingBuffer.write(bar));
  QCOMPARE(static_cast<int>(enumRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(enumRingBuffer.ringBufferElementsWritten()), 2);
  QCOMPARE(enumRingBuffer[0], foo);
  QCOMPARE(enumRingBuffer[1], bar);

  // Write values to the character array ring buffer
  myUnion_t charArrayValue1 = { { 'a', 'b', 'c' } };
  myUnion_t charArrayValue2 = { { 'd', 'e', 'f' } };
  QVERIFY(charArrayRingBuffer.write(charArrayValue1));
  QVERIFY(charArrayRingBuffer.write(charArrayValue2));
  QCOMPARE(static_cast<int>(charArrayRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(charArrayRingBuffer.ringBufferElementsWritten()), 2);
  QCOMPARE(static_cast<char>(charArrayRingBuffer[0].string[0]), 'a');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[0].string[1]), 'b');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[0].string[2]), 'c');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[1].string[0]), 'd');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[1].string[1]), 'e');
  QCOMPARE(static_cast<char>(charArrayRingBuffer[1].string[2]), 'f');

  // Test using myVoid_p type
  int   myInt   = 42;
  char  myChar  = 'a';
  float myFloat = 3.14;
  void *myVoid  = nullptr;

  // Add an integer to the ring buffer
  myVoid = static_cast<void *>(&myInt);
  QVERIFY(voidPtrRingBuffer.write(myVoid));

  // Add a character to the ring buffer
  myVoid = static_cast<void *>(&myChar);
  QVERIFY(voidPtrRingBuffer.write(myVoid));

  // Add a float to the ring buffer
  myVoid = static_cast<void *>(&myFloat);
  QVERIFY(voidPtrRingBuffer.write(myVoid));

  // Check that the elements in the ring buffer are correct
  void *bufferValue;
  QVERIFY(voidPtrRingBuffer.read(bufferValue));
  QCOMPARE(*static_cast<int *>(bufferValue), myInt);

  QVERIFY(voidPtrRingBuffer.read(bufferValue));
  QCOMPARE(*static_cast<char *>(bufferValue), myChar);

  QVERIFY(voidPtrRingBuffer.read(bufferValue));
  QCOMPARE(*static_cast<float *>(bufferValue), myFloat);
}

TEST_CASE(testRingBuffer, testDynamicRingBufferWrite)
{
  // Instantiate an instance of the ringBuffer class with that buffer
  MEM::ringBuffer<int> myRingBuffer(5);

  // Write elements to the buffer and check if write was successful
  QVERIFY(myRingBuffer.write(1));
  QVERIFY(myRingBuffer.write(2));
  QVERIFY(myRingBuffer.write(3));
  QVERIFY(myRingBuffer.write(4));
  QVERIFY(myRingBuffer.write(5));

  // Check if the buffer is full before attempting to write more data
  QVERIFY(myRingBuffer.ringBufferIsFull());

  // Try to write an element to a full buffer
  QVERIFY(!myRingBuffer.write(6));
}

TEST_CASE(testRingBuffer, testDynamicRingBufferRead)
{
  // Instantiate an instance of the ringBuffer class with that buffer
  MEM::ringBuffer<int> myRingBuffer(5);

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
  QVERIFY(myRingBuffer.ringBufferIsEmpty());
}

TEST_CASE(testRingBuffer, testDynamicRingBufferWriteMultiple)
{
  MEM::ringBuffer<int> myRingBuffer(5);
  int                  data[3] = { 1, 2, 3 };

  // Write multiple elements to the buffer and check if write was successful
  QVERIFY(myRingBuffer.write(data, 3));
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 5);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 3);

  // Check if the buffer is full before attempting to write more data
  QVERIFY(!myRingBuffer.ringBufferIsFull());

  // Try to write more elements to a full buffer
  QVERIFY(myRingBuffer.write(data, 2));

  QVERIFY(myRingBuffer.ringBufferIsFull());
}

TEST_CASE(testRingBuffer, testDynamicRingBufferReadMultiple)
{
  MEM::ringBuffer<int> myRingBuffer(5);
  int                  data[5] = { 1, 2, 3, 4, 5 };

  // Write elements to the buffer
  QVERIFY(myRingBuffer.write(data, 5));

  // Read multiple elements from the buffer and check if read was successful
  int values[3];
  QCOMPARE(static_cast<int>(myRingBuffer.read(values, 3)), 3);
  QCOMPARE(values[0], 1);
  QCOMPARE(values[1], 2);
  QCOMPARE(values[2], 3);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 5);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 2);

  // Try to read more elements from the buffer than are available
  QCOMPARE(static_cast<int>(myRingBuffer.read(values, 3)), 2);
}

TEST_CASE(testRingBuffer, testDynamicRingBufferPeek)
{
  // Instantiate an instance of the ringBuffer class with that buffer
  MEM::ringBuffer<int> myRingBuffer(5);

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);
  myRingBuffer.write(4);
  myRingBuffer.write(5);

  // Peek elements from the buffer and check if peek was successful
  int value;
  myRingBuffer.peek(value, 0);
  QCOMPARE(value, 1);
  myRingBuffer.peek(value, 1);
  QCOMPARE(value, 2);
  myRingBuffer.peek(value, 2);
  QCOMPARE(value, 3);
  myRingBuffer.peek(value, 3);
  QCOMPARE(value, 4);
  myRingBuffer.peek(value, 4);
  QCOMPARE(value, 5);
}

TEST_CASE(testRingBuffer, testDynamicRingBufferIndexOperator)
{
  MEM::ringBuffer<int> myRingBuffer(5);
  int                  data[5] = { 1, 2, 3, 4, 5 };

  // Write elements to the buffer
  QVERIFY(myRingBuffer.write(data, 5));

  // Check if the operator[] returns the expected values for the given indices
  QCOMPARE(myRingBuffer[0], 1);
  QCOMPARE(myRingBuffer[2], 3);
  QCOMPARE(myRingBuffer[4], 5);
}

TEST_CASE(testRingBuffer, testDynamicBufferReset)
{
  // Instantiate an instance of the ringBuffer class with that buffer
  MEM::ringBuffer<int> myRingBuffer(5);

  // Write elements to the buffer
  myRingBuffer.write(1);
  myRingBuffer.write(2);
  myRingBuffer.write(3);

  // Verify that the buffer is not empty
  QVERIFY(!myRingBuffer.ringBufferIsEmpty());

  // Reset the buffer
  myRingBuffer.reset();

  // Verify that the buffer is now empty
  QVERIFY(myRingBuffer.ringBufferIsEmpty());
}

TEST_CASE(testRingBuffer, testDynamicRingBufferOverwrite)
{
  // Instantiate an instance of the staticRingBuffer class with that buffer
  MEM::ringBuffer<int> myRingBuffer(3, MEM::RINGBUFFER_ALLOW_OVERWRITE);

  // Write more elements than the buffer capacity
  QVERIFY(myRingBuffer.write(1));
  QVERIFY(myRingBuffer.write(2));
  QVERIFY(myRingBuffer.write(3));
  QVERIFY(myRingBuffer.ringBufferIsFull());
  QVERIFY(myRingBuffer.write(4));
  QVERIFY(myRingBuffer.write(5));

  // Verify that the buffer is full
  QVERIFY(myRingBuffer.ringBufferIsFull());

  // Verify the content of the buffer
  QCOMPARE(myRingBuffer[0], 4);
  QCOMPARE(myRingBuffer[1], 5);
  QCOMPARE(myRingBuffer[2], 3);

  // Read an element to make space
  int value;
  QVERIFY(myRingBuffer.read(value));
  QCOMPARE(value, 3);
  QVERIFY(!myRingBuffer.ringBufferIsFull());
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 2);
  QVERIFY(!myRingBuffer.ringBufferIsFull());

  // Write another element to the buffer
  QVERIFY(myRingBuffer.write(6));

  // Verify that the buffer is full again and that the correct elements are in the buffer
  QVERIFY(myRingBuffer.ringBufferIsFull());
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementCount()), 3);
  QCOMPARE(static_cast<int>(myRingBuffer.ringBufferElementsWritten()), 3);
  QCOMPARE(myRingBuffer[0], 4);
  QCOMPARE(myRingBuffer[1], 5);
  QCOMPARE(myRingBuffer[2], 6);
}

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(testRingBuffer)
#include "debug/ring_buffer_test.moc"
#endif