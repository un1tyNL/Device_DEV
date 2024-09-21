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
   * @brief    Abstract base class for a statically allocated queue.
   * @details  Provides a common interface and shared logic for FIFO and LIFO queues.
   *           This class is derived from baseClass and inherits basic functionality.
   * @tparam   T
   *           The type of elements stored in the queue.
   * @tparam   queueSize
   *           The fixed size of the queue.
   */
  template <typename T, uint16_t queueSize>
  class queueBase : public baseClass
  {
  public:
    /**
     * @brief  Constructor to initialize the queue.
     */
    queueBase();

    /**
     * @brief      Add an element to the queue.
     * @param[in]  item
     *             The item to be added.
     * @return     `true` if the item was added successfully, `false` if the queue is full.
     * @note       This function must be implemented by derived classes (FIFO/LIFO).
     */
    virtual bool push(const T& item) = 0;

    /**
     * @brief       Remove the first element from the queue (FIFO or LIFO based).
     * @param[out]  item
     *              A reference to store the dequeued/popped item.
     * @return      true if the item was removed successfully, false if the queue is empty.
     * @note        This function must be implemented by derived classes (FIFO/LIFO).
     */
    virtual bool pop(T& item) = 0;

    /**
     * @brief   Check if the queue is empty.
     * @return  true if empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief   Check if the queue is full.
     * @return  true if full, false otherwise.
     */
    bool isFull() const;

  protected:
    T        m_data[queueSize]; //!< Statically allocated array for storage
    uint16_t m_head;            //!< The index of the head (for FIFO dequeue)
    uint16_t m_tail;            //!< The index of the tail (for FIFO enqueue or LIFO push)
    uint16_t m_currentSize;     //!< Number of elements currently in the queue

    /**
     * @brief      Increment an index circularly.
     * @param[in]  index
     *             The index to increment.
     * @return     The incremented index, wrapping around if necessary.
     */
    uint16_t incrementIndex(uint16_t index) const;

    /**
     * @brief      Decrement an index circularly.
     * @param[in]  index
     *             The index to decrement.
     * @return     The decremented index, wrapping around if necessary.
     */
    uint16_t decrementIndex(uint16_t index) const;
  };

  /**
   * @brief   A statically allocated FIFO queue implementation.
   * @tparam  T
   *          The type of elements stored in the queue.
   * @tparam  queueSize
   *          The fixed size of the queue.
   */
  template <typename T, uint16_t queueSize>
  class fifoQueue : public queueBase<T, queueSize>
  {
  public:
    /**
     * @brief      Add an element to the FIFO queue.
     * @param[in]  item
     *             The item to be added.
     * @return     `true` always, since FIFO queue overwrites the oldest element when full.
     */
    bool push(const T& item) override;

    /**
     * @brief       Remove the first element from the FIFO queue (dequeue).
     * @param[out]  item
     *              A reference to store the dequeued item.
     * @return      true if the item was removed successfully, false if the queue is empty.
     */
    bool pop(T& item) override;
  };

  /**
   * @brief   A statically allocated LIFO queue implementation (stack behavior).
   * @tparam  T
   *          The type of elements stored in the queue.
   * @tparam  queueSize
   *          The fixed size of the queue.
   */
  template <typename T, uint16_t queueSize>
  class lifoQueue : public queueBase<T, queueSize>
  {
  public:
    /**
     * @brief      Add an element to the LIFO queue (push to the "top").
     * @param[in]  item
     *             The item to be added.
     * @return     `true` if the item was added successfully, `false` if the stack is full.
     */
    bool push(const T& item) override;

    /**
     * @brief       Remove the last added element from the LIFO queue (pop from the "top").
     * @param[out]  item
     *              A reference to store the popped item.
     * @return      true if the item was removed successfully, false if the stack is empty.
     */
    bool pop(T& item) override;
  };

  /*************************************************************************\
   * Implementation
  \*************************************************************************/
  template <typename T, uint16_t queueSize>
  queueBase<T, queueSize>::queueBase() : m_head(0), m_tail(0), m_currentSize(0)
  {
  }

  template <typename T, uint16_t queueSize>
  uint16_t queueBase<T, queueSize>::incrementIndex(uint16_t index) const
  {
    return (index + 1) % queueSize;
  }

  template <typename T, uint16_t queueSize>
  uint16_t queueBase<T, queueSize>::decrementIndex(uint16_t index) const
  {
    return (index == 0) ? queueSize - 1 : index - 1;
  }

  template <typename T, uint16_t queueSize>
  bool queueBase<T, queueSize>::isEmpty() const
  {
    return m_currentSize == 0;
  }

  template <typename T, uint16_t queueSize>
  bool queueBase<T, queueSize>::isFull() const
  {
    return m_currentSize == queueSize;
  }

  // fifoQueue Implementation
  template <typename T, uint16_t queueSize>
  bool fifoQueue<T, queueSize>::push(const T& item)
  {
    if (this->isFull())
    {
      this->m_head = this->incrementIndex(this->m_head); // Overwrite oldest
    }
    else
    {
      this->m_currentSize++;
    }

    this->m_data[this->m_tail] = item;
    this->m_tail = this->incrementIndex(this->m_tail);

    return true; // Always successful
  }

  template <typename T, uint16_t queueSize>
  bool fifoQueue<T, queueSize>::pop(T& item)
  {
    if (this->isEmpty())
    {
      return false;
    }

    item = this->m_data[this->m_head];
    this->m_head = this->incrementIndex(this->m_head);
    this->m_currentSize--;

    return true;
  }

  // lifoQueue Implementation
  template <typename T, uint16_t queueSize>
  bool lifoQueue<T, queueSize>::push(const T& item)
  {
    if (this->isFull())
    {
      // Stack is full, cannot push
      return false;
    }

    this->m_data[this->m_tail] = item;
    this->m_tail = this->incrementIndex(this->m_tail);
    this->m_currentSize++;
    return true;
  }

  template <typename T, uint16_t queueSize>
  bool lifoQueue<T, queueSize>::pop(T& item)
  {
    if (this->isEmpty())
    {
      return false;
    }

    this->m_tail = this->decrementIndex(this->m_tail);
    item = this->m_data[this->m_tail];
    this->m_currentSize--;

    return true;
  }

} // namespace MEM
/*************************************************************************\
 * End of file
\*************************************************************************/
