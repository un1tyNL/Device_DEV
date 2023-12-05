#include "../../Tools/Testing/test_helper.hpp"
#include "../linked_list.hpp"

#if defined(QT_TESTLIB_LIB)
#include <QCoreApplication>
#include <QtTest/QtTest>
#else
#include "gtest/gtest.h"
#endif

#if defined(QT_TESTLIB_LIB)
class testLinkedList : public QObject
{
  Q_OBJECT

private slots:
  void testSinglyLinkedPush();
  void testSinglyLinkedPushFront();
  void testSinglyLinkedPushBack();
  void testSinglyLinkedPop();
  void testSinglyLinkedPopFront();
  void testSinglyLinkedPopBack();
  void testSinglyLinkedInsertAfter();
  void testSinglyLinkedInsertBefore();
  void testSinglyLinkedGetNodeAt();
  void testSinglyLinkedTestCircularity();

  void testDoublyLinkedPush();
  void testDoublyLinkedPushFront();
  void testDoublyLinkedPushBack();
  void testDoublyLinkedPop();
  void testDoublyLinkedPopFront();
  void testDoublyLinkedPopBack();
  void testDoublyLinkedInsertAfter();
  void testDoublyLinkedInsertBefore();
  void testDoublyLinkedGetNodeAt();
  void testDoublyLinkedTestCircularity();
  void testDoublyLinkedIteration();
};
#endif

/*************************************************************************\
* Singly linked list
\*************************************************************************/
TEST_CASE(testLinkedList, testSinglyLinkedPush)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1 = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2 = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3 = new MEM::sllNode<int>(3);

  list.push(node1);
  list.push(node2);
  list.push(node3);

  QCOMPARE(list.getHead(), node1);
  QCOMPARE(list.getHead()->getData(), node1->getData());
  QCOMPARE(list.getTail(), node3);
  QCOMPARE(list.getTail()->getData(), node3->getData());
  QCOMPARE(list.getCount(), static_cast<size_t>(3));

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testSinglyLinkedPushFront)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1 = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2 = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3 = new MEM::sllNode<int>(3);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  QCOMPARE(list.getHead(), node3);
  QCOMPARE(list.getTail(), node1);
  QCOMPARE(list.getCount(), static_cast<size_t>(3));

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testSinglyLinkedPushBack)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1 = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2 = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3 = new MEM::sllNode<int>(3);

  list.pushBack(node1);
  list.pushBack(node2);
  list.pushBack(node3);

  QCOMPARE(list.getHead(), node1);
  QCOMPARE(list.getTail(), node3);
  QCOMPARE(list.getCount(), static_cast<size_t>(3));

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testSinglyLinkedPop)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1 = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2 = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3 = new MEM::sllNode<int>(3);

  QCOMPARE(list.getHead(), nullptr);
  QCOMPARE(list.getTail(), nullptr);

  QCOMPARE(list.getCount(), static_cast<size_t>(0));
  list.push(node1);
  QCOMPARE(list.getCount(), static_cast<size_t>(1));
  list.push(node2);
  QCOMPARE(list.getCount(), static_cast<size_t>(2));
  list.push(node3);
  QCOMPARE(list.getCount(), static_cast<size_t>(3));

  QCOMPARE(list.getHead(), node1);
  QCOMPARE(list.getTail(), node3);

  QCOMPARE(list.pop(), node3);
  QCOMPARE(list.getCount(), static_cast<size_t>(2));
  QCOMPARE(list.pop(), node2);
  QCOMPARE(list.getCount(), static_cast<size_t>(1));
  QCOMPARE(list.pop(), node1);
  QCOMPARE(list.getCount(), static_cast<size_t>(0));
  QCOMPARE(list.pop(), nullptr);

  QCOMPARE(list.getHead(), nullptr);
  QCOMPARE(list.getTail(), nullptr);

  list.push(node1);
  QCOMPARE(list.getCount(), static_cast<size_t>(1));

  QCOMPARE(list.getHead(), node1);
  QCOMPARE(list.getTail(), node1);

  QCOMPARE(list.pop(node1), node1);
  QCOMPARE(list.getCount(), static_cast<size_t>(0));
  QCOMPARE(list.pop(node1), nullptr);

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testSinglyLinkedPopFront)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1 = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2 = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3 = new MEM::sllNode<int>(3);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  QCOMPARE(list.popFront(), node3);
  QCOMPARE(list.popFront(), node2);
  QCOMPARE(list.popFront(), node1);
  QCOMPARE(list.popFront(), nullptr);

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testSinglyLinkedPopBack)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1 = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2 = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3 = new MEM::sllNode<int>(3);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  QCOMPARE(list.popBack(), node1);
  QCOMPARE(list.popBack(), node2);
  QCOMPARE(list.popBack(), node3);
  QCOMPARE(list.popBack(), nullptr);

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testSinglyLinkedInsertAfter)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1   = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2   = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3   = new MEM::sllNode<int>(3);
  MEM::sllNode<int>*         newNode = new MEM::sllNode<int>(4);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  list.insertAfter(node2, newNode);

  QCOMPARE(list.getNodeAt(0), node3);
  QCOMPARE(list.getNodeAt(1), node2);
  QCOMPARE(list.getNodeAt(2), newNode);
  QCOMPARE(list.getNodeAt(3), node1);

  delete node1;
  delete node2;
  delete node3;
  delete newNode;
}

TEST_CASE(testLinkedList, testSinglyLinkedInsertBefore)
{
  MEM::singlyLinkedList<int> list;
  MEM::sllNode<int>*         node1   = new MEM::sllNode<int>(1);
  MEM::sllNode<int>*         node2   = new MEM::sllNode<int>(2);
  MEM::sllNode<int>*         node3   = new MEM::sllNode<int>(3);
  MEM::sllNode<int>*         newNode = new MEM::sllNode<int>(4);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  list.insertBefore(node2, newNode);

  QCOMPARE(list.getNodeAt(0), node3);
  QCOMPARE(list.getNodeAt(1), newNode);
  QCOMPARE(list.getNodeAt(2), node2);
  QCOMPARE(list.getNodeAt(3), node1);

  delete node1;
  delete node2;
  delete node3;
  delete newNode;
}

TEST_CASE(testLinkedList, testSinglyLinkedGetNodeAt)
{
  // Create a list with 5 nodes containing the values 0, 1, 2, 3, 4
  MEM::singlyLinkedList<int> list;
  for (int i = 0; i < 5; i++)
  {
    MEM::sllNode<int>* node = new MEM::sllNode<int>(i);
    list.pushBack(node);
  }

  // Test getting nodes at valid and invalid indices
  QVERIFY(list.getNodeAt(0)->getData() == 0);
  QVERIFY(list.getNodeAt(4)->getData() == 4);
  QVERIFY(list.getNodeAt(2)->getData() == 2);
  QVERIFY(list.getNodeAt(5) == nullptr);

  for (int i = 0; i < 5; i++)
  {
    delete list.pop();
  }
}

TEST_CASE(testLinkedList, testSinglyLinkedTestCircularity)
{
  // Create a list with 5 nodes containing the values 0, 1, 2, 3, 4
  MEM::singlyLinkedList<int> list;
  for (int i = 0; i < 5; i++)
  {
    MEM::sllNode<int>* node = new MEM::sllNode<int>(i);
    list.pushBack(node);
  }

  // Test non-circular list
  QVERIFY(!list.testCircularity());

  // Make the list circular and test again
  list.makeCircular();
  QVERIFY(list.testCircularity());

  // Break the circularity and test again
  list.breakCircularity();
  QVERIFY(!list.testCircularity());

  for (int i = 0; i < 5; i++)
  {
    delete list.pop();
  }
}

TEST_CASE(testLinkedList, testDoublyLinkedPush)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);

  list.push(node1);
  list.push(node2);
  list.push(node3);

  QCOMPARE(list.getHead(), node1);
  QCOMPARE(list.getTail(), node3);
  QCOMPARE(list.getHead()->getData(), 1);
  QCOMPARE(list.getTail()->getData(), 3);
  QCOMPARE(list.getCount(), static_cast<size_t>(3));
}

/*************************************************************************\
* Doubly linked list
\*************************************************************************/
TEST_CASE(testLinkedList, testDoublyLinkedPushFront)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  QCOMPARE(list.getHead(), node3);
  QCOMPARE(list.getTail(), node1);
  QCOMPARE(list.getCount(), static_cast<size_t>(3));
}

TEST_CASE(testLinkedList, testDoublyLinkedPushBack)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);

  list.pushBack(node1);
  list.pushBack(node2);
  list.pushBack(node3);

  QCOMPARE(list.getHead(), node1);
  QCOMPARE(list.getTail(), node3);
  QCOMPARE(list.getCount(), static_cast<size_t>(3));
}

TEST_CASE(testLinkedList, testDoublyLinkedPop)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);

  list.push(node1);
  list.push(node2);
  list.push(node3);

  QCOMPARE(list.pop(), node3);
  QCOMPARE(list.pop(), node2);
  QCOMPARE(list.pop(), node1);
  QCOMPARE(list.pop(), nullptr);
  QCOMPARE(list.getHead(), nullptr);
  QCOMPARE(list.getTail(), nullptr);
  QCOMPARE(list.getCount(), static_cast<size_t>(0));
}

TEST_CASE(testLinkedList, testDoublyLinkedPopFront)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);

  list.pushFront(node1);
  list.pushFront(node2);
  list.pushFront(node3);

  QCOMPARE(list.popFront(), node3);
  QCOMPARE(list.popFront(), node2);
  QCOMPARE(list.popFront(), node1);
  QCOMPARE(list.popFront(), nullptr);
}

TEST_CASE(testLinkedList, testDoublyLinkedPopBack)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);

  list.pushBack(node1);
  list.pushBack(node2);
  list.pushBack(node3);

  QCOMPARE(list.popBack(), node3);
  QCOMPARE(list.popBack(), node2);
  QCOMPARE(list.popBack(), node1);
  QCOMPARE(list.popBack(), nullptr);

  delete node1;
  delete node2;
  delete node3;
}

TEST_CASE(testLinkedList, testDoublyLinkedInsertAfter)
{
  // Create a new doubly linked list with 3 nodes
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);
  list.pushFront(node1);
  list.pushBack(node2);
  list.pushBack(node3);

  // Insert a new node after the second node
  MEM::dllNode<int>* newNode = new MEM::dllNode<int>(4);
  list.insertAfter(node2, newNode);

  // Check that the new node was inserted in the correct position
  QCOMPARE(list.getNodeAt(0), node1);
  QCOMPARE(list.getNodeAt(1), node2);
  QCOMPARE(list.getNodeAt(2), newNode);
  QCOMPARE(list.getNodeAt(3), node3);

  // Delete the nodes to prevent memory leaks
  delete node1;
  delete node2;
  delete node3;
  delete newNode;
}

TEST_CASE(testLinkedList, testDoublyLinkedInsertBefore)
{
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1   = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2   = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3   = new MEM::dllNode<int>(3);
  MEM::dllNode<int>*         newNode = new MEM::dllNode<int>(4);

  list.pushBack(node1);
  list.pushBack(node2);
  list.pushBack(node3);

  list.insertBefore(node2, newNode);

  QCOMPARE(list.getNodeAt(0), node1);
  QCOMPARE(list.getNodeAt(1), newNode);
  QCOMPARE(list.getNodeAt(2), node2);
  QCOMPARE(list.getNodeAt(3), node3);

  delete node1;
  delete node2;
  delete node3;
  delete newNode;
}

TEST_CASE(testLinkedList, testDoublyLinkedGetNodeAt)
{
  // Create a list with 5 nodes containing the values 0, 1, 2, 3, 4
  MEM::doublyLinkedList<int> list;
  for (int i = 0; i < 5; i++)
  {
    MEM::dllNode<int>* node = new MEM::dllNode<int>(i);
    list.pushBack(node);
  }

  // Test getting nodes at valid and invalid indices
  QVERIFY(list.getNodeAt(0)->getData() == 0);
  QVERIFY(list.getNodeAt(4)->getData() == 4);
  QVERIFY(list.getNodeAt(2)->getData() == 2);
  QVERIFY(list.getNodeAt(5) == nullptr);

  for (int i = 0; i < 5; i++)
  {
    delete list.pop();
  }
}

TEST_CASE(testLinkedList, testDoublyLinkedTestCircularity)
{
  // Create a list with 5 nodes containing the values 0, 1, 2, 3, 4
  MEM::doublyLinkedList<int> list;
  for (int i = 0; i < 5; i++)
  {
    MEM::dllNode<int>* node = new MEM::dllNode<int>(i);
    list.pushBack(node);
  }

  // Test non-circular list
  QVERIFY(!list.testCircularity());

  // Make the list circular and test again
  list.makeCircular();
  QVERIFY(list.testCircularity());

  // Break the circularity and test again
  list.breakCircularity();
  QVERIFY(!list.testCircularity());

  for (int i = 0; i < 5; i++)
  {
    delete list.pop();
  }
}

TEST_CASE(testLinkedList, testDoublyLinkedIteration)
{
  MEM::doublyLinkedList<int> list;

  MEM::dllNode<int>* nodes[5];
  for (int i = 0; i < 5; i++)
  {
    nodes[i] = new MEM::dllNode<int>();
    nodes[i]->setData(i + 1);
    list.push(nodes[i]);
  }

  // Forward iteration
  int expected_value = 1;
  for (auto node = list.getHead(); node != nullptr; node = node->getNext())
  {
    QCOMPARE(node->getData(), expected_value);
    if (node->getNext() != nullptr)
    {
      QCOMPARE(node->getNext()->getPrev(), node);
    }
    expected_value++;
  }

  // Backward iteration
  expected_value = 5;
  for (auto node = list.getTail(); node != nullptr; node = node->getPrev())
  {
    QCOMPARE(node->getData(), expected_value);
    if (node->getPrev() != nullptr)
    {
      QCOMPARE(node->getPrev()->getNext(), node);
    }
    expected_value--;
  }

  for (int i = 0; i < 5; i++)
  {
    delete list.pop();
  }
}

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(testLinkedList)
#include "linked_list_test.moc"
#endif
