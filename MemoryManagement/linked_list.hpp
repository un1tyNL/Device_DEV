/*************************************************************************\
* Documentation
\*************************************************************************/
/**
 * @file     linked_list.hpp
 * @version  0.1
 * @brief    Definition of singlyLinkedList and doublyLinkedList classes.
 * @details  The `singlyLinkedList` class is a singly linked list implementation that uses nodes containing a reference to the next node.
 *           The `doublyLinkedList` class is a doubly linked list implementation that uses nodes containing a reference to both the next and
 *           previous nodes. The nodes are not allocated by the list itself, but should be allocated and supplied by the user. Each node is
 *           a templated class, allowing for the storage of different data types in the same list.
 * @note     To use the `singlyLinkedList` class, follow these steps:
 *           - Instantiate an instance of the `singlyLinkedList` class with the desired node type as a template parameter, like this:
 *             `singlyLinkedList<int, sllNode<int>*> myList;`.
 *           - Use the `push()` function to add nodes to the list, passing in a pointer to the node, like this:
 *             `int data = 42;
 *             sllNode<int>* node = new sllNode<int>(data);
 *             myList.push(node);`.
 *           - Use the `pop()` function to remove nodes from the list. It will return a pointer to the removed node, like this:
 *             `sllNode<int>* node = myList.pop();`.
 *           - Use the `testCircularity()` function to check if the list is circular.
 *           - Use the `makeCircular()` function to make the list circular.
 *           - Use the `breakCircularity()` function to break the circularity.
 *           To use the `doublyLinkedList` class, follow these steps:
 *           - Instantiate an instance of the `doublyLinkedList` class with the desired node type as a template parameter, like this:
 *             `doublyLinkedList<int, dllNode<int>*> myList;`.
 *           - Use the `push()` function to add nodes to the list, passing in a pointer to the node, like this:
 *             `int data = 42;
 *             dllNode<int>* node = new dllNode<int>(data);
 *             myList.push(node);`.
 *           - Use the `pop()` function to remove nodes from the list. It will return a pointer to the removed node, like this:
 *             `dllNode<int>* node = myList.pop();`.
 *           - Use the `testCircularity()` function to check if the list is circular.
 *           - Use the `makeCircular()` function to make the list circular.
 *           - Use the `breakCircularity()` function to break the circularity.
 */
#pragma once
/*************************************************************************\
* Includes
\*************************************************************************/
#include "global.hpp"

/*************************************************************************\
 * Prototypes
\*************************************************************************/
namespace MEM
{
  /**
   * @brief    A node in a singly linked list.
   * @details  This class represents a node in a singly linked list.
   *           The node contains a reference to the next node in the list
   *           and some data of type `T`.
   * @tparam   T
   *           Data type of the element stored in the node.
   */
  template <typename T>
  class sllNode
  {
  public:
    /**
     * @brief  Default constructor that initializes a node with a null reference to the next node and no data.
     */
    sllNode() : m_next(nullptr), m_data() {};

    /**
     * @brief      Constructor that initializes a node with a null reference to the next node and the specified data.
     * @param[in]  data
     *             Data to be stored in the node.
     */
    sllNode(T data) : m_next(nullptr), m_data(data) {};

    /**
     * @brief     Constructor that initializes the node with given data and the next node pointer.
     * @param[in] data 
     *            The data to be stored in the node.
     * @param[in] next 
     *            A pointer to the next node in the list.
     */
    sllNode(T data, sllNode* next) : m_data(data), m_next(next) {};

    /**
     * @brief  Destructor for the node.
     */
    ~sllNode() {};

    /**
     * @brief   Returns a reference to the next node in the list.
     * @return  Reference to the next node in the list.
     */
    sllNode<T>* getNext() const
    {
      return m_next;
    };

    /**
     * @brief      Sets the next node in the list.
     * @param[in]  next
     *             Pointer to the next node in the list.
     */
    void setNext(sllNode<T>* next)
    {
      m_next = next;
    };

    /**
     * @brief   Returns the data stored in the node.
     * @return  Data stored in the node.
     */
    T getData() const
    {
      return m_data;
    };

    /**
     * @brief      Sets the data stored in the node.
     * @param[in]  data
     *             Data to be stored in the node.
     */
    void setData(T data)
    {
      m_data = data;
    };

  protected:
    sllNode<T>* m_next; //!< Pointer to the next node in the list.
    T           m_data; //!< Data stored in the node.
  };

  /**
   * @brief    A node in a doubly linked list.
   * @details  This class represents a node in a doubly linked list.
   *           The node contains a reference to the next and previous nodes
   *           in the list and some data of type `T`.
   * @tparam   T
   *           Data type of the element stored in the node.
   */
  template <typename T>
  class dllNode : public sllNode<T>
  {
  public:
    /**
     * @brief  Default constructor that initializes a node with a null reference to the next and previous nodes and no data.
     */
    dllNode() : sllNode<T>(), m_prev(nullptr) {};

    /**
     * @brief      Constructor that initializes a node with a null reference to the next and previous nodes and the specified data.
     * @param[in]  data
     *             Data to be stored in the node.
     */
    dllNode(T data) : sllNode<T>(data), m_prev(nullptr) {};

    /**
     * @brief      Constructor that initializes the node with given data, the next node pointer and the previous node pointer.
     * @param[in]  data
     *             The data to be stored in the node.
     * @param[in]  next
     *             A pointer to the next node in the list.
     * @param[in]  prev
     *             A pointer to the previous node in the list.
     */
    dllNode(T data, dllNode<T>* next, dllNode<T>* prev) : sllNode<T>(data, next), m_prev(prev) {};

    /**
     * @brief  Destructor for the node.
     */
    ~dllNode() {};

    /**
     * @brief   Returns a reference to the previous node in the list.
     * @return  Reference to the previous node in the list.
     */
    dllNode<T>* getPrev() const
    {
      return m_prev;
    };

    /**
     * @brief      Sets the previous node in the list.
     * @param[in]  prev
     *             Pointer to the previous node in the list.
     */
    void setPrev(dllNode<T>* prev)
    {
      m_prev = prev;
    };

    /**
     * @brief   Returns a reference to the next node in the list.
     * @return  A reference to the next node in the list.
     */
    dllNode<T>* getNext() const
    {
      return static_cast<dllNode<T>*>(sllNode<T>::getNext());
    }

    /**
     * @brief      Sets the next node in the list.
     * @param[in]  next
     *             Pointer to the next node in the list.
     */
    void setNext(dllNode<T>* next)
    {
      sllNode<T>::setNext(static_cast<sllNode<T>*>(next));
    }

  private:
    dllNode<T>* m_prev; //!< Pointer to the previous node in the list.
  };

  /**
   * @brief    The singlyLinkedList class is a linked list data structure that contains a list of sllNode elements.
   * @details  The singlyLinkedList class provides a way to store and manipulate a collection of elements
   *           in a singly linked list. It supports adding and removing elements at the front, back and
   *           arbitrary positions of the list, as well as getting the count and node at a specific index.
   * @tparam   T
   *           Type of data stored in the linked list.
   */
  template <typename T, typename nodeType = sllNode<T>*>
  class singlyLinkedList
  {
  public:
    /**
     * @brief  Constructor that initializes an empty singly linked list.
     */
    singlyLinkedList() : m_head(nullptr), m_tail(nullptr), m_count(0), m_circular(false) {};

    /**
     * @brief  Default destructor, which doesn't destroy the nodes in the list as they aren't managed by the singlyLinkedList class.
     */
    ~singlyLinkedList() {};

    /**
     * @brief      Adds a node to the back of the list.
     * @param[in]  node
     *             Pointer to the node to add.
     */
    virtual void push(nodeType node);

    /**
     * @brief      Adds a node to the front of the singly linked list.
     * @param[in]  node
     *             Pointer to the node to be added.
     */
    virtual void pushFront(nodeType node);

    /**
     * @brief      Adds a node to the back of the singly linked list.
     * @param[in]  node
     *             Pointer to the node to be added.
     */
    virtual void pushBack(nodeType node);

    /**
     * @brief   Removes the node at the back of the list and returns it.
     * @return  Pointer to the node that was removed, or nullptr if the list is empty.
     */
    virtual nodeType pop();

    /**
     * @brief      Removes a specific node from the list.
     * @param[in]  node
     *             Pointer to the node to be removed.
     * @return     Pointer to the removed node, or nullptr if the node was not found.
     */
    virtual nodeType pop(nodeType node);

    /**
     * @brief   Removes the node from the front of the singly linked list.
     * @return  Pointer to the removed node, or nullptr if the list is empty.
     */
    virtual nodeType popFront();

    /**
     * @brief   Removes the node from the back of the singly linked list.
     * @return  Pointer to the removed node, or nullptr if the list is empty.
     */
    virtual nodeType popBack();

    /**
     * @brief      Adds a node after the specified node in the singly linked list.
     * @param[in]  node
     *             Pointer to the node after which the new node should be added.
     * @param[in]  newNode
     *             Pointer to the new node to be added.
     */
    virtual void insertAfter(nodeType node, nodeType newNode);

    /**
     * @brief      Adds a node before the specified node in the singly linked list.
     * @param[in]  node
     *             Pointer to the node before which the new node should be added.
     * @param[in]  newNode
     *             Pointer to the new node to be added.
     */
    virtual void insertBefore(nodeType node, nodeType newNode);

    /**
     * @brief      Returns a pointer to the node at the specified index in the singly linked list.
     * @param[in]  index
     *             Index of the node to be returned.
     * @return     Pointer to the node at the specified index, or nullptr if the index is out of bounds.
     */
    nodeType getNodeAt(size_t index) const;

    /**
     * @brief   Checks if the singly linked list is circular.
     * @return  true if the singly linked list is circular, false otherwise.
     */
    virtual bool testCircularity() const;

    /**
     * @brief  Makes the singly linked list circular.
     */
    virtual void makeCircular()
    {
      if (m_head != nullptr && m_tail->getNext() == nullptr)
      {
        m_tail->setNext(m_head);
      }
      m_circular = true;
    }

    /**
     * @brief  Breaks the circularity of the singly linked list.
     */
    virtual void breakCircularity()
    {
      if (m_head != nullptr && m_tail->getNext() != nullptr)
      {
        m_tail->setNext(nullptr);
      }
      m_circular = false;
    }

    /**
     * @brief   Returns the number of nodes in the singly linked list.
     * @return  The number of nodes in the singly linked list.
     */
    size_t getCount() const
    {
      return m_count;
    }

    /**
     * @brief   Returns a pointer to the head node in the singly linked list.
     * @return  Pointer to the head node in the singly linked list.
     */
    virtual nodeType getHead() const
    {
      return m_head;
    }

    /**
     * @brief   Returns a pointer to the tail node in the singly linked list.
     * @return  Pointer to the tail node in the singly linked list.
     */
    virtual nodeType getTail() const
    {
      return m_tail;
    }

  protected:
    nodeType m_head;     //!< Pointer to the head node of the singly linked list.
    nodeType m_tail;     //!< Pointer to the tail node of the singly linked list.
    size_t   m_count;    //!< The number of nodes in the singly linked list.
    bool     m_circular; //!< Indicates if the linked list is currently circularly linked.
  };

  /**
   * @brief    The doublyLinkedList class is a linked list data structure that contains a list of dllNode elements.
   * @details  The doublyLinkedList class is derived from the singlyLinkedList class and provides a way to store and manipulate
   *           a collection of elements in a doubly linked list. It supports adding and removing elements at the front, back and
   *           arbitrary positions of the list, as well as getting the count and node at a specific index.
   * @tparam   T
   *           Type of data stored in the linked list.
   */
  template <typename T>
  class doublyLinkedList : public singlyLinkedList<T, dllNode<T>*>
  {
  public:
    /**
     * @brief  Default constructor.
     */
    doublyLinkedList() {};

    /**
     * @brief  Destructor.
     */
    ~doublyLinkedList() {};

    /**
     * @brief      Adds a node to the back of the list.
     * @param[in]  node
     *             Pointer to the node to add.
     */
    void push(dllNode<T>* node) override;

    /**
     * @brief      Add a node to the front of the list.
     * @param[in]  node 
     *             Pointer to the node to add.
     */
    void pushFront(dllNode<T>* node) override;

    /**
     * @brief      Add a node to the back of the list.
     * @param[in]  node 
     *             Pointer to the node to add.
     */
    void pushBack(dllNode<T>* node) override;

    /**
     * @brief   Removes the node at the back of the list and returns it.
     * @return  Pointer to the node that was removed, or nullptr if the list is empty.
     */
    dllNode<T>* pop() override
    {
      return popBack();
    };

    /**
     * @brief   Remove and return the node at the front of the list.
     * @return  Pointer to the node at the front of the list, or nullptr if the list is empty.
     */
    dllNode<T>* popFront() override;

    /**
     * @brief   Remove and return the node at the back of the list.
     * @return  Pointer to the node at the back of the list, or nullptr if the list is empty.
     */
    dllNode<T>* popBack() override;

    /**
     * @brief      Add a node after a given node.
     * @param[in]  prevNode 
     *             Pointer to the node to insert after.
     * @param[in]  newNode 
     *             Pointer to the node to insert.
     */
    void insertAfter(dllNode<T>* prevNode, dllNode<T>* newNode) override;

    /**
     * @brief      Add a node before a given node.
     * @param[in]  nextNode 
     *             Pointer to the node to insert before.
     * @param[in]  newNode 
     *             Pointer to the node to insert.
     */
    void insertBefore(dllNode<T>* nextNode, dllNode<T>* newNode) override;

    /**
     * @brief   Returns a pointer to the tail node in the doubly linked list.
     * @return  Pointer to the tail node in the doubly linked list.
     */
    dllNode<T>* getTail() const override
    {
      return static_cast<dllNode<T>*>(singlyLinkedList<T, dllNode<T>*>::getTail());
    }

    /**
     * @brief   Returns a pointer to the head node in the doubly linked list.
     * @return  Pointer to the head node in the doubly linked list.
     */
    dllNode<T>* getHead() const override
    {
      return static_cast<dllNode<T>*>(singlyLinkedList<T, dllNode<T>*>::getHead());
    }

    /**
     * @brief  Makes the list circular by connecting the tail to the head.
     */
    void makeCircular() override
    {
      if (this->m_count > 0)
      {
        this->m_tail->setNext(this->m_head);
        this->m_head->setPrev(this->m_tail);
        this->m_circular = true;
      }
    }

    /**
     * @brief  Breaks the circularity of the list by disconnecting the tail from the head.
     */
    void breakCircularity() override
    {
      if (this->m_count > 0)
      {
        this->m_tail->setNext(nullptr);
        this->m_head->setPrev(nullptr);
        this->m_circular = false;
      }
    }
  };
} // namespace MEM
/*************************************************************************\
 * Implementation
\*************************************************************************/
namespace MEM
{

  template <typename T, typename nodeType>
  void singlyLinkedList<T, nodeType>::push(nodeType node)
  {
    this->pushBack(node);
  }

  template <typename T, typename nodeType>
  void singlyLinkedList<T, nodeType>::pushFront(nodeType node)
  {
    if (m_head == nullptr)
    {
      m_head = node;
      m_tail = node;
    }
    else
    {
      node->setNext(m_head);
      m_head = node;
    }
    m_count++;
  }

  template <typename T, typename nodeType>
  void singlyLinkedList<T, nodeType>::pushBack(nodeType node)
  {
    if (m_tail == nullptr)
    {
      m_head = node;
      m_tail = node;
    }
    else
    {
      m_tail->setNext(node);
      m_tail = node;
    }
    m_count++;
  }

  template <typename T, typename nodeType>
  nodeType singlyLinkedList<T, nodeType>::pop(nodeType node)
  {
    if (m_head == nullptr)
    {
      return nullptr;
    }

    if (m_head == node)
    {
      return popFront();
    }

    nodeType current = m_head;
    while (current->getNext() != nullptr && current->getNext() != node)
    {
      current = current->getNext();
    }

    if (current->getNext() == nullptr)
    {
      return nullptr;
    }

    nodeType removedNode = current->getNext();
    current->setNext(removedNode->getNext());
    if (removedNode == m_tail)
    {
      m_tail = current;
    }
    removedNode->setNext(nullptr);
    --m_count;

    return removedNode;
  }

  template <typename T, typename nodeType>
  nodeType singlyLinkedList<T, nodeType>::pop()
  {
    return popBack();
  }

  template <typename T, typename nodeType>
  nodeType singlyLinkedList<T, nodeType>::popFront()
  {
    if (m_head == nullptr)
    {
      return nullptr;
    }

    nodeType removedNode = m_head;
    m_head               = m_head->getNext();
    if (m_head == nullptr)
    {
      m_tail = nullptr;
    }
    removedNode->setNext(nullptr);
    --m_count;

    return removedNode;
  }

  template <typename T, typename nodeType>
  nodeType singlyLinkedList<T, nodeType>::popBack()
  {
    if (m_count == 0)
    {
      return nullptr;
    }

    nodeType node = m_tail;
    if (m_count == 1)
    {
      m_head = nullptr;
      m_tail = nullptr;
    }
    else
    {
      nodeType prev = getNodeAt(m_count - 2);
      prev->setNext(nullptr);
      m_tail = prev;
    }

    --m_count;
    return node;
  }

  template <typename T, typename nodeType>
  void singlyLinkedList<T, nodeType>::insertAfter(nodeType node, nodeType newNode)
  {
    if (node == nullptr) // Invalid node, can't insert after it
    {
      return;
    }
    if (node == m_tail) // Node is at the back of the list, so just push back instead
    {
      pushBack(newNode);
      return;
    }

    newNode->setNext(node->getNext());
    node->setNext(newNode);
    m_count++;
  }

  template <typename T, typename nodeType>
  void singlyLinkedList<T, nodeType>::insertBefore(nodeType node, nodeType newNode)
  {
    if (node == nullptr) // Invalid node, can't insert before it
    {
      return;
    }
    if (node == m_head) // Node is at the front of the list, so just push front instead
    {
      pushFront(newNode);
      return;
    }

    nodeType previous = m_head;
    while (previous != nullptr && previous->getNext() != node)
    {
      previous = previous->getNext();
    }

    if (previous != nullptr)
    {
      newNode->setNext(node);
      previous->setNext(newNode);
      m_count++;
    }
  }

  template <typename T, typename nodeType>
  nodeType singlyLinkedList<T, nodeType>::getNodeAt(size_t index) const
  {
    if (index >= m_count) // Out of bounds
    {
      return nullptr;
    }

    nodeType current = m_head;
    for (size_t i = 0; i < index; i++)
    {
      current = current->getNext();
    }

    return current;
  }

  template <typename T, typename nodeType>
  bool singlyLinkedList<T, nodeType>::testCircularity() const
  {
    bool     isCircular = false;
    nodeType fast       = m_head;
    nodeType slow       = m_head;

    while (fast->getNext() != nullptr && fast->getNext() != nullptr)
    {
      fast = fast->getNext()->getNext();
      slow = slow->getNext();

      if (fast == slow)
      {
        isCircular = true;
        break;
      }
    }

    return isCircular;
  }

  template <typename T>
  void doublyLinkedList<T>::push(dllNode<T>* node)
  {
    doublyLinkedList<T>::pushBack(node);
  }

  template <typename T>
  void doublyLinkedList<T>::pushFront(dllNode<T>* node)
  {
    if (this->m_head == nullptr)
    {
      this->m_head = this->m_tail = node;
    }
    else
    {
      node->setNext(this->m_head);
      this->m_head->setPrev(node);
      this->m_head = node;
    }
    this->m_count++;
  }

  template <typename T>
  void doublyLinkedList<T>::pushBack(dllNode<T>* node)
  {
    if (this->m_head == nullptr)
    {
      this->m_head = this->m_tail = node;
    }
    else
    {
      node->setPrev(this->m_tail);
      this->m_tail->setNext(node);
      this->m_tail = node;
    }
    this->m_count++;
  }

  template <typename T>
  dllNode<T>* doublyLinkedList<T>::popFront()
  {
    if (this->m_count == 0)
    {
      return nullptr;
    }

    dllNode<T>* node = this->m_head;

    if (this->m_head == this->m_tail)
    {
      this->m_head = this->m_tail = nullptr;
    }
    else
    {
      this->m_head = node->getNext();
      this->m_head->setPrev(nullptr);
    }

    this->m_count--;
    node->setNext(nullptr);

    return node;
  }

  template <typename T>
  dllNode<T>* doublyLinkedList<T>::popBack()
  {
    if (this->m_count == 0)
    {
      return nullptr;
    }

    dllNode<T>* node = this->m_tail;

    if (this->m_head == this->m_tail)
    {
      this->m_head = this->m_tail = nullptr;
    }
    else
    {
      this->m_tail = node->getPrev();
      this->m_tail->setNext(nullptr);
    }

    this->m_count--;
    node->setPrev(nullptr);

    return node;
  }

  template <typename T>
  void doublyLinkedList<T>::insertAfter(dllNode<T>* current, dllNode<T>* node)
  {
    if (current == this->m_tail)
    {
      this->pushBack(node);
    }
    else
    {
      node->setPrev(static_cast<dllNode<T>*>(current));
      node->setNext(current->getNext());
      current->getNext()->setPrev(node);
      current->setNext(node);
      this->m_count++;
    }
  }

  template <typename T>
  void doublyLinkedList<T>::insertBefore(dllNode<T>* current, dllNode<T>* node)
  {
    if (current == this->m_head)
    {
      this->pushFront(node);
    }
    else
    {
      node->setNext(current);
      node->setPrev(current->getPrev());
      current->getPrev()->setNext(node);
      current->setPrev(node);
      this->m_count++;
    }
  }
} // namespace MEM
/*************************************************************************\
 * End of file
\*************************************************************************/
