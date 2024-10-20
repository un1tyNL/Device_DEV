#include "../../Tools/Testing/test_helper.hpp"
#include "../doubly_linked_list.hpp"
#include "../singly_linked_list.hpp"
#include <iterator> // Include this if using reverse range-based for loop

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
  void testSinglyLinkedIteration();

  void testDoublyLinkedPush();
  void testDoublyLinkedPushFront();
  void testDoublyLinkedPushBack();
  void testDoublyLinkedPop();
  void testDoublyLinkedPopFront();
  void testDoublyLinkedPopBack();
  void testDoublyLinkedInsertAfter();
  void testDoublyLinkedInsertBefore();
  void testDoublyLinkedGetNodeAt();
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


  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
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

  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
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

  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
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

  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
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

  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
}

TEST_CASE(testLinkedList, testSinglyLinkedGetNodeAt)
{
  MEM::singlyLinkedList<int> list;
  for (int i = 0; i < 5; i++)
  {
    MEM::sllNode<int>* node = new MEM::sllNode<int>(i);
    list.pushBack(node);
  }

  QVERIFY(list.getNodeAt(0) != nullptr);
  QCOMPARE(list.getNodeAt(0)->getData(), 0);
  QVERIFY(list.getNodeAt(4) != nullptr);
  QCOMPARE(list.getNodeAt(4)->getData(), 4);
  QVERIFY(list.getNodeAt(2) != nullptr);
  QCOMPARE(list.getNodeAt(2)->getData(), 2);
  QVERIFY(list.getNodeAt(5) == nullptr);


  while (list.getCount() > 0)
  {
    delete list.popFront();
  }
}

TEST_CASE(testLinkedList, testSinglyLinkedIteration)
{
  MEM::singlyLinkedList<int> list;

  MEM::sllNode<int>* nodes[5];
  for (int i = 0; i < 5; ++i)
  {
    nodes[i] = new MEM::sllNode<int>(i + 1);
    list.pushBack(nodes[i]);
  }

  // 1. Forward iteration using getNext()
  int expected_value = 1;
  for (auto node = list.getHead(); node != nullptr; node = node->getNext())
  {
    QCOMPARE(node->getData(), expected_value);
    expected_value++;
  }

  // 2. Forward iteration using iterators
  expected_value = 1;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    QCOMPARE(*it, expected_value);
    expected_value++;
  }

  // 3. Forward iteration using range-based for loop
  expected_value = 1;
  for (const int& value : list)
  {
    QCOMPARE(value, expected_value);
    expected_value++;
  }


  while (list.getCount() > 0)
  {
    delete list.popFront();
  }
}


/*************************************************************************\
* Doubly linked list
\*************************************************************************/
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


  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
}

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


  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
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


  delete list.popFront();
  delete list.popFront();
  delete list.popFront();
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


  delete node1;
  delete node2;
  delete node3;
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


  delete node1;
  delete node2;
  delete node3;
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
  MEM::doublyLinkedList<int> list;
  MEM::dllNode<int>*         node1 = new MEM::dllNode<int>(1);
  MEM::dllNode<int>*         node2 = new MEM::dllNode<int>(2);
  MEM::dllNode<int>*         node3 = new MEM::dllNode<int>(3);
  list.pushFront(node1);
  list.pushBack(node2);
  list.pushBack(node3);

  MEM::dllNode<int>* newNode = new MEM::dllNode<int>(4);
  list.insertAfter(node2, newNode);

  QCOMPARE(list.getNodeAt(0), node1);
  QCOMPARE(list.getNodeAt(1), node2);
  QCOMPARE(list.getNodeAt(2), newNode);
  QCOMPARE(list.getNodeAt(3), node3);


  while (list.getCount() > 0)
  {
    delete list.popFront();
  }
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


  while (list.getCount() > 0)
  {
    delete list.popFront();
  }
}

TEST_CASE(testLinkedList, testDoublyLinkedGetNodeAt)
{
  MEM::doublyLinkedList<int> list;
  for (int i = 0; i < 5; i++)
  {
    MEM::dllNode<int>* node = new MEM::dllNode<int>(i);
    list.pushBack(node);
  }

  QVERIFY(list.getNodeAt(0) != nullptr);
  QCOMPARE(list.getNodeAt(0)->getData(), 0);

  QVERIFY(list.getNodeAt(4) != nullptr);
  QCOMPARE(list.getNodeAt(4)->getData(), 4);

  QVERIFY(list.getNodeAt(2) != nullptr);
  QCOMPARE(list.getNodeAt(2)->getData(), 2);

  QVERIFY(list.getNodeAt(5) == nullptr);


  while (list.getCount() > 0)
  {
    delete list.popFront();
  }
}

TEST_CASE(testLinkedList, testDoublyLinkedIteration)
{
  MEM::doublyLinkedList<int> list;

  MEM::dllNode<int>* nodes[5];
  for (int i = 0; i < 5; ++i)
  {
    nodes[i] = new MEM::dllNode<int>(i + 1);
    list.pushBack(nodes[i]);
  }


  // 1. Forward iteration using getNext()
  int expected_value = 1;
  for (auto node = list.getHead(); node != nullptr; node = node->getNext())
  {
    QCOMPARE(node->getData(), expected_value);
    if (node->getNext() != nullptr)
    {
      // Verify the linkage between nodes
      QCOMPARE(node->getNext()->getPrev(), node);
    }
    expected_value++;
  }


  // 2. Backward iteration using getPrev()
  expected_value = 5;
  for (auto node = list.getTail(); node != nullptr; node = node->getPrev())
  {
    QCOMPARE(node->getData(), expected_value);
    if (node->getPrev() != nullptr)
    {
      // Verify the linkage between nodes
      QCOMPARE(node->getPrev()->getNext(), node);
    }
    expected_value--;
  }


  // 3. Forward iteration using iterators
  expected_value = 1;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    QCOMPARE(*it, expected_value);
    expected_value++;
  }


  // 4. Reverse iteration using iterators
  expected_value = 5;
  for (auto it = list.rbegin(); it != list.rend(); --it)
  {
    QCOMPARE(*it, expected_value);
    expected_value--;
  }


  // 5. Forward iteration using range-based for loop
  expected_value = 1;
  for (const int& value : list)
  {
    QCOMPARE(value, expected_value);
    expected_value++;
  }


  // 6. Reverse iteration using reverse() in a range-based for loop
  expected_value = 5;
  for (const int& value : list.reverse())
  {
    QCOMPARE(value, expected_value);
    expected_value--;
  }


  while (list.getCount() > 0)
  {
    delete list.popFront();
  }
}

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(testLinkedList)
#include "linked_list_test.moc"
#endif
