/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     ring_buffer.hpp
 * @version  0.3
 * @brief    Definition of the ringBuffer class.
 * @details  The `ringBuffer` class is a circular buffer implementation with statically allocated memory.
 *           It is used to buffer data between processes, threads, or interrupts without dynamic memory allocation.
 *           It can be configured to either overwrite old data with new or discard new data when the buffer is full.
 *
 *           The template parameters are the data type (`T`) and the buffer size in bytes (`bufferSize`).
 *           The class calculates at compile time how many elements of type `T` can fit into the specified buffer size.
 *
 *           To use the `ringBuffer` class, follow these steps:
 *           -# Instantiate an instance of the `ringBuffer` class with the desired data type and buffer size in bytes
 *              as template parameters, like this: `ringBuffer<int, 64> myRingBuffer;`.
 *           -# Use the `write()` function to add elements to the buffer, like this: `myRingBuffer.write(42);`.
 *           -# Use the `read()` function to read elements from the buffer, like this: `int myValue; myRingBuffer.read(myValue);`.
 *           -# Check the return value of `write()` and `read()` to determine whether or not an operation was successful.
 *
 * @note     The buffer size (`bufferSize`) must be large enough to hold at least one element of type `T`.
 *           If it is not, a compile-time error will occur.
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
   * @brief  Enumeration type for specifying the overwrite behavior of the buffer when it is full.
   */
  enum ringBufferOverwrite_e
  {
    RINGBUFFER_NO_OVERWRITE,   //!< Don't overwrite the oldest element in the buffer when it is full.
    RINGBUFFER_ALLOW_OVERWRITE //!< Overwrite the oldest element in the buffer when it is full.
  };

  /**
   * @brief    Class template for a ring buffer with statically allocated memory.
   * @details  This class implements the functionality of a ring buffer without dynamic memory allocation.
   *           The `bufferSize` specifies the size of the buffer in bytes.
   *           The class calculates how many elements of type `T` can fit into the buffer.
   *           The buffer uses an internal statically allocated array for storing the elements.
   * @tparam   T
   *           Data type of the elements in the ring buffer.
   * @tparam   bufferSize
   *           The size of the buffer in bytes.
   */
  template <typename T, std::size_t bufferSize>
  class ringBuffer
  {
  public:
    /**
     * @brief      Constructor that initializes the ring buffer.
     * @param[in]  overwrite
     *             Specifies whether to overwrite the oldest element in the buffer when it is full.
     *             Default is `RINGBUFFER_NO_OVERWRITE`.
     */
    explicit ringBuffer(MEM::ringBufferOverwrite_e overwrite = MEM::RINGBUFFER_NO_OVERWRITE);

    /**
     * @brief    Reset the ring buffer.
     * @details  This function resets the ring buffer to its initial state, with the read and write indices set to zero
     *           and the number of items in the buffer set to zero.
     */
    void reset();

    /**
     * @brief      Set the overwrite behavior of the buffer when it is full.
     * @param[in]  overwrite
     *             The overwrite behavior to set.
     */
    void setOverwriteBehavior(MEM::ringBufferOverwrite_e overwrite);

    /**
     * @brief   Get the current overwrite behavior of the buffer.
     * @return  The current overwrite behavior.
     */
    MEM::ringBufferOverwrite_e getOverwriteBehavior() const;

    /**
     * @brief   Check if the ring buffer is empty.
     * @return  `true` if the buffer is empty, `false` otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief   Check if the ring buffer is full.
     * @return  `true` if the buffer is full, `false` otherwise.
     */
    bool isFull() const;

    /**
     * @brief   Get the number of elements currently stored in the ring buffer.
     * @return  The number of elements currently stored.
     */
    std::size_t count() const;

    /**
     * @brief   Get the maximum number of elements that can be stored in the ring buffer.
     * @return  The capacity of the ring buffer.
     */
    constexpr std::size_t capacity() const;

    /**
     * @brief      Write a single element to the ring buffer.
     * @details    If the buffer is full and the overwrite behavior allows overwriting,
     *             the oldest data in the buffer will be overwritten.
     * @param[in]  data
     *             The element to be written to the buffer.
     * @return     `true` if the data was written successfully, `false` if the buffer is full
     *             and overwriting is not allowed.
     */
    bool write(const T& data);

    /**
     * @brief      Write multiple elements to the ring buffer.
     * @details    Writes up to `dataCount` elements from the `data` array into the ring buffer.
     *             Stops if the buffer becomes full and overwriting is not allowed.
     * @param[in]  data
     *             The array of elements to write.
     * @param[in]  dataCount
     *             The number of elements to write.
     * @return     The number of elements actually written to the buffer.
     */
    std::size_t write(const T data[], std::size_t dataCount);

    /**
     * @brief       Read a single element from the ring buffer.
     * @details     Removes the oldest element from the buffer and stores it in `data`.
     * @param[out]  data
     *              The variable to store the read element.
     * @return      `true` if an element was read successfully, `false` if the buffer is empty.
     */
    bool read(T& data);

    /**
     * @brief       Read multiple elements from the ring buffer.
     * @details     Reads up to `dataCount` elements from the buffer and stores them in `data`.
     * @param[out]  data
     *              The array to store the read elements.
     * @param[in]   dataCount
     *              The maximum number of elements to read.
     * @return      The number of elements actually read from the buffer.
     */
    std::size_t read(T data[], std::size_t dataCount);

    /**
     * @brief       Peek at an element in the ring buffer without removing it.
     * @param[out]  data
     *              The variable to store the peeked element.
     * @param[in]   index
     *              The zero-based index of the element to peek at, relative to the oldest element.
     * @return      `true` if the element was peeked successfully, `false` if the index is out of range.
     */
    bool peek(T& data, std::size_t index) const;

    /**
     * @brief      Access an element in the ring buffer by index.
     * @details    Provides read-only access to elements in the buffer without removing them.
     * @param[in]  index
     *             The zero-based index of the element to access, relative to the oldest element.
     * @return     A const reference to the element at the specified index.
     * @throws     std::out_of_range if the index is out of range.
     */
    const T& operator[](std::size_t index) const;

  private:
    static constexpr std::size_t elementCount = bufferSize / sizeof(T); //!< Number of elements that can fit in the buffer.
    static_assert(elementCount > 0, "Buffer size is too small to hold even one element of type T.");

    T                          m_dataArray[elementCount]; //!< The statically allocated array used as the ring buffer.
    MEM::ringBufferOverwrite_e m_overwriteSetting;        //!< Overwrite behavior when the buffer is full.
    std::size_t                m_readIndex;               //!< Index of the current read position.
    std::size_t                m_writeIndex;              //!< Index of the current write position.
    std::size_t                m_elementsStored;          //!< Number of elements currently stored in the buffer.

    /**
     * @brief      Advances the index by one position, wrapping around if necessary.
     * @param[in]  index
     *             The current index.
     * @return     The next index position.
     */
    std::size_t nextIndex(std::size_t index) const;
  };

} // namespace MEM

/*************************************************************************\
 * Implementation
\*************************************************************************/
namespace MEM
{
  template <typename T, std::size_t bufferSize>
  ringBuffer<T, bufferSize>::ringBuffer(MEM::ringBufferOverwrite_e overwrite) :
    m_overwriteSetting(overwrite),
    m_readIndex(0),
    m_writeIndex(0),
    m_elementsStored(0)
  {
    static_assert(std::is_default_constructible<T>::value, "Type T must be default constructible.");
    // Initialize the buffer elements if necessary (e.g., for complex types)
    // For POD types, this is optional.
  }

  template <typename T, std::size_t bufferSize>
  void ringBuffer<T, bufferSize>::reset()
  {
    m_readIndex      = 0;
    m_writeIndex     = 0;
    m_elementsStored = 0;
  }

  template <typename T, std::size_t bufferSize>
  void ringBuffer<T, bufferSize>::setOverwriteBehavior(MEM::ringBufferOverwrite_e overwrite)
  {
    m_overwriteSetting = overwrite;
  }

  template <typename T, std::size_t bufferSize>
  MEM::ringBufferOverwrite_e ringBuffer<T, bufferSize>::getOverwriteBehavior() const
  {
    return m_overwriteSetting;
  }

  template <typename T, std::size_t bufferSize>
  bool ringBuffer<T, bufferSize>::isEmpty() const
  {
    return m_elementsStored == 0;
  }

  template <typename T, std::size_t bufferSize>
  bool ringBuffer<T, bufferSize>::isFull() const
  {
    return m_elementsStored == elementCount;
  }

  template <typename T, std::size_t bufferSize>
  std::size_t ringBuffer<T, bufferSize>::count() const
  {
    return m_elementsStored;
  }

  template <typename T, std::size_t bufferSize>
  constexpr std::size_t ringBuffer<T, bufferSize>::capacity() const
  {
    return elementCount;
  }

  template <typename T, std::size_t bufferSize>
  bool ringBuffer<T, bufferSize>::write(const T& data)
  {
    if (isFull())
    {
      if (m_overwriteSetting == MEM::RINGBUFFER_ALLOW_OVERWRITE)
      {
        // Overwrite the oldest data
        m_dataArray[m_writeIndex] = data;
        m_writeIndex              = nextIndex(m_writeIndex);
        m_readIndex               = nextIndex(m_readIndex); // Move read index forward
        // m_elementsStored remains the same
        return true;
      }
      else
      {
        // Cannot write, buffer is full
        return false;
      }
    }
    else
    {
      // There is space in the buffer
      m_dataArray[m_writeIndex] = data;
      m_writeIndex              = nextIndex(m_writeIndex);
      ++m_elementsStored;
      return true;
    }
  }

  template <typename T, std::size_t bufferSize>
  std::size_t ringBuffer<T, bufferSize>::write(const T data[], std::size_t dataCount)
  {
    std::size_t itemsWritten = 0;

    for (std::size_t i = 0; i < dataCount; ++i)
    {
      if (write(data[i]))
      {
        ++itemsWritten;
      }
      else
      {
        // Buffer is full and overwriting is not allowed
        break;
      }
    }

    return itemsWritten;
  }

  template <typename T, std::size_t bufferSize>
  bool ringBuffer<T, bufferSize>::read(T& data)
  {
    if (isEmpty())
    {
      // Buffer is empty
      return false;
    }
    else
    {
      data        = m_dataArray[m_readIndex];
      m_readIndex = nextIndex(m_readIndex);
      --m_elementsStored;
      return true;
    }
  }

  template <typename T, std::size_t bufferSize>
  std::size_t ringBuffer<T, bufferSize>::read(T data[], std::size_t dataCount)
  {
    std::size_t itemsRead = 0;

    for (std::size_t i = 0; i < dataCount; ++i)
    {
      if (read(data[i]))
      {
        ++itemsRead;
      }
      else
      {
        // Buffer is empty
        break;
      }
    }

    return itemsRead;
  }

  template <typename T, std::size_t bufferSize>
  bool ringBuffer<T, bufferSize>::peek(T& data, std::size_t index) const
  {
    if (index >= m_elementsStored)
    {
      // Index is out of range
      return false;
    }
    else
    {
      std::size_t actualIndex = (m_readIndex + index) % elementCount;
      data                    = m_dataArray[actualIndex];
      return true;
    }
  }

  template <typename T, std::size_t bufferSize>
  const T& ringBuffer<T, bufferSize>::operator[](std::size_t index) const
  {
    if (index >= m_elementsStored)
    {
      throw std::out_of_range("Index out of range");
    }
    else
    {
      std::size_t actualIndex = (m_readIndex + index) % elementCount;
      return m_dataArray[actualIndex];
    }
  }

  template <typename T, std::size_t bufferSize>
  std::size_t ringBuffer<T, bufferSize>::nextIndex(std::size_t index) const
  {
    return (index + 1) % elementCount;
  }

} // namespace MEM

/*************************************************************************\
 * End of file
\*************************************************************************/
