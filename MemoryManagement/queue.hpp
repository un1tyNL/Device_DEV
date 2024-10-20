#pragma once
/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     queue.hpp
 * @version  0.1
 * @brief    Definition of FIFO and LIFO queue classes with iterator support.
 * @details  This file provides template implementations for statically allocated
 *           FIFO (First-In-First-Out) and LIFO (Last-In-First-Out) queues with
 *           support for iterators to enable range-based for loops.
 *           These queues are designed for use in embedded systems or other
 *           environments where dynamic memory allocation is not desirable.
 *
 * @note     **Thread Safety Note:**
 *           Iterating over the queue is **not thread-safe**. If the queue can be modified
 *           by other threads during iteration, external synchronization is required.
 *
 *           **Usage Instructions:**
 *           - Instantiate a queue with the desired data type and size:
 *             - `fifoQueue<int, 64> myFifoQueue;`
 *             - `lifoQueue<float, 128> myLifoQueue;`
 *           - Use `push()` to add elements and `pop()` to remove elements.
 *           - Use range-based for loops to iterate over elements:
 *             - `for (const auto& item : myFifoQueue) { // process item }`
 *             - Or simply:
 *               `for (const auto& item : myFifoQueue) { ... }`
 *           - Check the return value of `push()` and `pop()` to determine success or failure.
 *
 *           **Template Parameters:**
 *           - `T`: The type of elements stored in the queue.
 *           - `queueSize`: The fixed size of the queue.
 *
 *           The queue size (`queueSize`) must be greater than zero.
 *           If it is zero, a compile-time error will occur.
 */

/*************************************************************************\
 * Includes
\*************************************************************************/
#pragma once
#include "global.hpp"

namespace MEM
{
  /**
   * @brief    Abstract base class for a statically allocated queue.
   * @details  Provides a common interface and shared logic for FIFO and LIFO queues.
   * @tparam   T          The type of elements stored in the queue.
   * @tparam   queueSize  The fixed size of the queue.
   */
  template <typename T, size_t queueSize>
  class queueBase : public baseClass
  {
  public:
    static_assert(queueSize > 0, "queueSize must be greater than zero");

    /**
     * @brief  Constructor to initialize the queue.
     */
    queueBase();

    // Rule of Five
    queueBase(const queueBase&) = delete;
    queueBase& operator=(const queueBase&) = delete;
    queueBase(queueBase&&) = delete;
    queueBase& operator=(queueBase&&) = delete;
    virtual ~queueBase() = default;

    /**
     * @brief      Adds an element to the queue.
     * @param[in]  item  The item to be added.
     * @return     `true` if the item was added successfully, `false` otherwise.
     * @note       This function must be implemented by derived classes (FIFO/LIFO).
     */
    virtual bool push(const T& item) = 0;

    /**
     * @brief      Adds an element to the queue (move semantics).
     * @param[in]  item  The item to be added.
     * @return     `true` if the item was added successfully, `false` otherwise.
     * @note       This function must be implemented by derived classes (FIFO/LIFO).
     */
    virtual bool push(T&& item) = 0;

    /**
     * @brief       Removes an element from the queue.
     * @param[out]  item  A reference to store the popped item.
     * @return      `true` if the item was removed successfully, `false` if the queue is empty.
     */
    virtual bool pop(T& item) = 0;

    /**
     * @brief   Checks if the queue is empty.
     * @return  `true` if empty, `false` otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief   Checks if the queue is full.
     * @return  `true` if full, `false` otherwise.
     */
    bool isFull() const;

    /**
     * @brief   Retrieves the current number of elements in the queue.
     * @return  The number of elements in the queue.
     */
    size_t size() const;

    // Iterator support
    class iterator;
    iterator begin();
    iterator end();

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

  protected:
    T      m_data[queueSize]; //!< Statically allocated array for storage
    size_t m_head;            //!< The index of the head (for FIFO dequeue)
    size_t m_tail;            //!< The index of the tail (for FIFO enqueue or LIFO push)
    size_t m_currentSize;     //!< Number of elements currently in the queue

    mutable std::mutex m_mutex; //!< Mutex for thread safety

    /**
     * @brief      Increments an index circularly.
     * @param[in]  index  The index to increment.
     * @return     The incremented index, wrapping around if necessary.
     */
    size_t incrementIndex(size_t index) const;

    /**
     * @brief      Decrements an index circularly.
     * @param[in]  index  The index to decrement.
     * @return     The decremented index, wrapping around if necessary.
     */
    size_t decrementIndex(size_t index) const;
  };

  // Iterator Implementation
  template <typename T, size_t queueSize>
  class queueBase<T, queueSize>::iterator
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;

    iterator(queueBase<T, queueSize>* queue, size_t index, size_t count)
      : m_queue(queue), m_index(index), m_count(count)
    {
    }

    reference operator*()
    {
      return m_queue->m_data[m_index];
    }

    pointer operator->()
    {
      return &(m_queue->m_data[m_index]);
    }

    iterator& operator++()
    {
      m_index = m_queue->incrementIndex(m_index);
      ++m_count;
      return *this;
    }

    iterator operator++(int)
    {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const iterator& other) const
    {
      return m_queue == other.m_queue && m_count == other.m_count;
    }

    bool operator!=(const iterator& other) const
    {
      return !(*this == other);
    }

  private:
    queueBase<T, queueSize>* m_queue;
    size_t                   m_index;
    size_t                   m_count;
  };

  template <typename T, size_t queueSize>
  typename queueBase<T, queueSize>::iterator queueBase<T, queueSize>::begin()
  {
    return iterator(this, m_head, 0);
  }

  template <typename T, size_t queueSize>
  typename queueBase<T, queueSize>::iterator queueBase<T, queueSize>::end()
  {
    return iterator(this, m_tail, m_currentSize);
  }

  // Const Iterator Implementation
  template <typename T, size_t queueSize>
  class queueBase<T, queueSize>::const_iterator
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const T*;
    using reference         = const T&;

    const_iterator(const queueBase<T, queueSize>* queue, size_t index, size_t count)
      : m_queue(queue), m_index(index), m_count(count)
    {
    }

    reference operator*() const
    {
      return m_queue->m_data[m_index];
    }

    pointer operator->() const
    {
      return &(m_queue->m_data[m_index]);
    }

    const_iterator& operator++()
    {
      m_index = m_queue->incrementIndex(m_index);
      ++m_count;
      return *this;
    }

    const_iterator operator++(int)
    {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) const
    {
      return m_queue == other.m_queue && m_count == other.m_count;
    }

    bool operator!=(const const_iterator& other) const
    {
      return !(*this == other);
    }

  private:
    const queueBase<T, queueSize>* m_queue;
    size_t                         m_index;
    size_t                         m_count;
  };

  template <typename T, size_t queueSize>
  typename queueBase<T, queueSize>::const_iterator queueBase<T, queueSize>::begin() const
  {
    return const_iterator(this, m_head, 0);
  }

  template <typename T, size_t queueSize>
  typename queueBase<T, queueSize>::const_iterator queueBase<T, queueSize>::end() const
  {
    return const_iterator(this, m_tail, m_currentSize);
  }

  /*************************************************************************\
   * Implementation of queueBase
  \*************************************************************************/
  template <typename T, size_t queueSize>
  queueBase<T, queueSize>::queueBase() : m_head(0), m_tail(0), m_currentSize(0)
  {
  }

  template <typename T, size_t queueSize>
  size_t queueBase<T, queueSize>::incrementIndex(size_t index) const
  {
    return (index + 1) % queueSize;
  }

  template <typename T, size_t queueSize>
  size_t queueBase<T, queueSize>::decrementIndex(size_t index) const
  {
    return (index == 0) ? queueSize - 1 : index - 1;
  }

  template <typename T, size_t queueSize>
  bool queueBase<T, queueSize>::isEmpty() const
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_currentSize == 0;
  }

  template <typename T, size_t queueSize>
  bool queueBase<T, queueSize>::isFull() const
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_currentSize == queueSize;
  }

  template <typename T, size_t queueSize>
  size_t queueBase<T, queueSize>::size() const
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_currentSize;
  }

  /*************************************************************************\
   * fifoQueue Implementation
  \*************************************************************************/
  template <typename T, size_t queueSize>
  class fifoQueue : public queueBase<T, queueSize>
  {
  public:
    bool push(const T& item) override;
    bool push(T&& item) override;
    bool pop(T& item) override;
    bool peek(T& item) const;
  };

  template <typename T, size_t queueSize>
  bool fifoQueue<T, queueSize>::push(const T& item)
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == queueSize)
    {
      // Overwrite oldest element
      this->m_head = this->incrementIndex(this->m_head);
    }
    else
    {
      this->m_currentSize++;
    }

    this->m_data[this->m_tail] = item;
    this->m_tail               = this->incrementIndex(this->m_tail);

    return true; // Always successful
  }

  template <typename T, size_t queueSize>
  bool fifoQueue<T, queueSize>::push(T&& item)
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == queueSize)
    {
      // Overwrite oldest element
      this->m_head = this->incrementIndex(this->m_head);
    }
    else
    {
      this->m_currentSize++;
    }

    this->m_data[this->m_tail] = std::move(item);
    this->m_tail               = this->incrementIndex(this->m_tail);

    return true; // Always successful
  }

  template <typename T, size_t queueSize>
  bool fifoQueue<T, queueSize>::pop(T& item)
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == 0)
    {
      return false;
    }

    item = std::move(this->m_data[this->m_head]);
    this->m_head = this->incrementIndex(this->m_head);
    this->m_currentSize--;

    return true;
  }

  template <typename T, size_t queueSize>
  bool fifoQueue<T, queueSize>::peek(T& item) const
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == 0)
    {
      return false;
    }

    item = this->m_data[this->m_head];
    return true;
  }

  /*************************************************************************\
   * lifoQueue Implementation
  \*************************************************************************/
  template <typename T, size_t queueSize>
  class lifoQueue : public queueBase<T, queueSize>
  {
  public:
    bool push(const T& item) override;
    bool push(T&& item) override;
    bool pop(T& item) override;
    bool peek(T& item) const;
  };

  template <typename T, size_t queueSize>
  bool lifoQueue<T, queueSize>::push(const T& item)
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == queueSize)
    {
      // Stack is full, cannot push
      return false;
    }

    this->m_data[this->m_tail] = item;
    this->m_tail               = this->incrementIndex(this->m_tail);
    this->m_currentSize++;
    return true;
  }

  template <typename T, size_t queueSize>
  bool lifoQueue<T, queueSize>::push(T&& item)
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == queueSize)
    {
      // Stack is full, cannot push
      return false;
    }

    this->m_data[this->m_tail] = std::move(item);
    this->m_tail               = this->incrementIndex(this->m_tail);
    this->m_currentSize++;
    return true;
  }

  template <typename T, size_t queueSize>
  bool lifoQueue<T, queueSize>::pop(T& item)
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == 0)
    {
      return false;
    }

    this->m_tail = this->decrementIndex(this->m_tail);
    item = std::move(this->m_data[this->m_tail]);
    this->m_currentSize--;

    return true;
  }

  template <typename T, size_t queueSize>
  bool lifoQueue<T, queueSize>::peek(T& item) const
  {
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if (this->m_currentSize == 0)
    {
      return false;
    }

    size_t tempTail = this->decrementIndex(this->m_tail);
    item = this->m_data[tempTail];
    return true;
  }

} // namespace MEM

/*************************************************************************\
 * End of file
\*************************************************************************/
