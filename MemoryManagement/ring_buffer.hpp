/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     ring_buffer.hpp
 * @version  0.1
 * @brief    Definition of ringBuffer and staticRingBuffer classes.
 * @details  The ringBuffer class is a circular buffer implementation with a memory pool that can be
 *           dynamically or statically allocated. It is used to buffer data between processes, threads or
 *           interrupts. It can be configured to either overwrite old data with new or discard new data when
 *           the buffer is full. The staticRingBuffer is a template derived class of ringBuffer that
 *           takes a compile-time assigned piece of memory to be used as a ring buffer. The number of elements
 *           that can be stored in the ring buffer is specified by the template parameter.
 * @note     To use the `ringBuffer` class, follow these steps:
 *           -# Instantiate an instance of the `ringBuffer` class with the desired element count and data type as a template parameter,
 *              like this: `ringBuffer<int> myRingBuffer(10);`.
 *           -# Use the `write()` function to add elements to the buffer, like this: `int data = 42; myRingBuffer.write(data)`.
 *           -# Use the `read()` function to read elements from the buffer, like this: `int myValue; myRingBuffer.read(myValue);`.
 *           -# Check the return value of `write()` and `read()` to determine whether or not an operation was successful.
 *           To use the `staticRingBuffer` class, follow these steps:
 *           -# Instantiate an instance of the `staticRingBuffer` class with the desired element count and data type as template
 *              parameters, like this: `staticRingBuffer<int, 10> myRingBuffer;`.
 *           -# Use the `write()` function to add elements to the buffer, like this: `myRingBuffer.write(42)`.
 *           -# Use the `read()` function to read elements from the buffer, like this: `int myValue; myRingBuffer.read(myValue);`.
 *           -# Check the return value of `write()` and `read()` to determine whether or not an operation was successful.
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
  typedef enum ringBufferOverwrite
  {
    RINGBUFFER_NO_OVERWRITE,   //!< Don't overwrite the oldest element in the buffer when it is full.
    RINGBUFFER_ALLOW_OVERWRITE //!< Overwrite the oldest element in the buffer when it is full.
  } ringBufferOverwrite_e;

  /**
   * @brief    Base class for a ring buffer.
   * @details  This class implements the basic functionality of a ring buffer, including
   *           writing to and reading from the buffer, as well as keeping track of the
   *           number of elements stored in the buffer and the current indices for writing
   *           and reading. The `elementCount` parameter specifies the maximum number of
   *           elements that can be stored in the buffer, and the `overWrite` parameter
   *           specifies whether to overwrite the oldest element in the buffer when writing
   *           and the buffer is full.
   * @tparam   T
   *           Data type of the elements in the ring buffer.
   */
  template <typename T>
  class ringBuffer
  {
  public:
    /**
     * @brief      Constructor that initializes the buffer with the specified maximum number of elements.
     * @param[in]  m_elementCount
     *             The maximum number of elements that can be stored in the buffer.
     */
    ringBuffer(const size_t m_elementCount);

    /**
     * @brief      Constructor that initializes the buffer with the specified maximum number of elements and overwrite setting.
     * @param[in]  m_elementCount
     *             The maximum number of elements that can be stored in the buffer.
     * @param[in]  overWrite
     *             Specifies whether to overwrite the oldest element in the buffer when it is full.
     */
    ringBuffer(const size_t m_elementCount, MEM::ringBufferOverwrite_e overWrite);

    /**
     * @brief      Constructor that initializes the buffer with the specified maximum number of elements and initial data.
     * @param[in]  m_elementCount
     *             The maximum number of elements that can be stored in the buffer.
     * @param[in]  array
     *             Pointer to an array to be used as ringbuffer
     */
    ringBuffer(const size_t m_elementCount, T const *const array);

    /**
     * @brief      Constructor that initializes the buffer with the specified maximum number of elements, initial data and overwrite
     *             setting.
     * @param[in]  m_elementCount
     *             The maximum number of elements that can be stored in the buffer.
     * @param[in]  array
     *             Pointer to an array to be used as ringbuffer
     * @param[in]  overWrite
     *             Specifies whether to overwrite the oldest element in the buffer when it is full.
     */
    ringBuffer(const size_t m_elementCount, T const *const array, MEM::ringBufferOverwrite_e overWrite);

    /**
     * @brief    Destroy the ring buffer object.
     * @details  This destructor is called when a ring buffer object is destroyed. It deallocates any dynamically allocated memory used by
     *           the object and performs any other necessary cleanup.
     */
    ~ringBuffer();

    /**
     * @brief      Set the default behavior for overwrite and branch execution.
     * @param[in]  overwrite
     *             Default behavior for overwrite.
     */
    void setOverwriteBehavior(MEM::ringBufferOverwrite_e overwrite);

    /**
     * @brief   Gets the configured behaviour of the ringbuffer.
     * @return  Returns the configured behaviour.
     */
    MEM::ringBufferOverwrite_e getOverwriteBehavior() const;
    ;

    /**
     * @brief    Reset the ring buffer.
     * @details  This function resets the ring buffer to its initial state, with the read and write pointers set to the beginning of the
     *           buffer and the number of items in the buffer set to zero.
     */
    void reset();

    /**
     * @brief   Tests if the ring buffer has no items stored.
     * @return  Returns true if there are no items to be read from the ring buffer.
     */
    bool ringBufferIsEmpty() const;
    ;

    /**
     * @brief   Checks if the ring buffer is full.
     * @return  True if the buffer is full, false otherwise.
     */
    bool ringBufferIsFull() const;

    /**
     * @brief    Get the number total of elements in the ring buffer.
     * @details  This function returns the number of items currently stored in the ring buffer. It can be used to determine the
     *           number of items that can be read from the buffer in a single call to the read function.
     * @return   The total number of items that can be stored in the array.
     */
    size_t ringBufferElementCount() const;
    ;

    /**
     * @brief    Get the size of an item in the ring buffer.
     * @details  This function returns the size of an item in the ring buffer in bytes. It can be used to determine the number of bytes
     *           that can be read from the buffer in a single call to the read function.
     * @return   The size of an item in the ring buffer in bytes.
     */
    size_t ringBufferElementSize() const;
    ;

    /**
     * @brief   Returns the size of the ring buffer's array.
     * @return  The size of the ring buffer's array in bytes.
     */
    size_t ringBufferSize() const;
    ;

    /**
     * @brief   Returns the number of items currently stored in the ring buffer.
     * @return  The number of items currently stored in the ring buffer.
     */
    size_t ringBufferElementsWritten() const;
    ;

    /**
     * @brief      Write a single item to the ring buffer.
     * @details    This function writes a single item of type `T` to the ring buffer. If the buffer is full and the overwrite setting allows
     *             overwriting of old data, the oldest data in the buffer will be overwritten. If the overwrite setting is set to
     *             `RINGBUFFER_DISALLOW_OVERWRITE`, the function will return `false` and no data will be written to the buffer. This
     *             function takes a reference to the data item as input and returns a boolean indicating whether the write operation was
     * successful.
     * @param[in]  dataRef
     *             A reference to the element to be written to the buffer.
     * @return     True if the data was written to the buffer successfully, false if the buffer is full and the overwrite setting is set to
     *             `RINGBUFFER_DISALLOW_OVERWRITE`.
     */
    bool write(T &dataRef);

    /**
     * @brief      Writes a single element to the ring buffer.
     * @details    This function writes a single element of type `T` to the ring buffer. If the buffer is full
     *             and the overwrite behavior allows overwriting of old data, the oldest data in the buffer
     *             will be overwritten. If the overwrite behavior is set to `RINGBUFFER_DISALLOW_OVERWRITE`,
     *             the function will return `false` and no data will be written to the buffer.
     * @param[in]  data
     *             The element to be written to the buffer.
     * @return     True if the data was written to the buffer successfully, false if the buffer is full
     *             and the overwrite behavior is set to `RINGBUFFER_DISALLOW_OVERWRITE`.
     */
    bool write(const T &data);

    /**
     * @brief      Writes multiple items to the ring buffer.
     * @param[in]  data
     *             An array of items to write to the buffer.
     * @param[in]  dataCount
     *             The number of items in the `data` array.
     * @return     True if the write operation was successful, false if there was not enough space in the buffer to write all of the items
     * and the `RINGBUFFER_ALLOW_OVERWRITE` option is not set.
     */
    bool write(T data[], size_t &dataCount);

    /**
     * @brief      Writes multiple items to the ring buffer.
     * @param[in]  data
     *             An array of items to write to the buffer.
     * @param[in]  dataCount
     *             The number of items in the `data` array, that are intended to be written to the ringbuffer.
     * @return     The number of items written to the ringbuffer.
     */
    size_t write(T data[], const size_t dataCount);

    /**
     * @brief       Reads an item from the ring buffer and removes it from the buffer.
     * @param[out]  data
     *              A reference to a variable to store the read item.
     * @return      true if the read operation was successful (i.e. there was an item in the buffer to read), false otherwise.
     * @note        The read operation is destructive, meaning that the value of the item is set to 0 after being read.
     */
    bool read(T &data);

    /**
     * @brief       Reads multiple items from the ring buffer and removes them from the buffer.
     * @param[out]  data
     *              A reference to an array to store the read items.
     * @param[in]   dataRead
     *              The maximum number of items to read.
     * @return      The number of items that were actually read.
     * @note        The read operation is destructive, meaning that the value of the item is set to 0 after being read.
     */
    size_t read(T data[], const size_t dataRead);

    /**
     * @brief       Reads an item from the ring buffer without removing it from the buffer.
     * @param[in]   index
     *              The offset from the read pointer to read from, with 0 being the item at the read pointer.
     * @param[out]  data
     *              A pointer to a variable to store the peeked item.
     * @return      true if the peek operation was successful, false otherwise.
     * @note        The peek operation is non-destructive, meaning that the item is not modified in the buffer and the read pointer is not
     *              moved.
     */
    bool peek(T &data, const size_t index);

    /**
     * @brief      Overload of the array subscript operator for reading items from the ring buffer.
     * @param[in]  index
     *             The absolute index of the item to read.
     * @return     The item at the specified index.
     * @note       This operator does not modify the item in the buffer or move the read pointer.
     */
    T operator[](const size_t index) const;

  private:

    typedef bool (ringBuffer::*writeFunctions)(T &data); //!< This type definition is for a pointer to a function that writes a single item.
    writeFunctions m_writeFunctionType[2];               //!< An array of pointers to functions that write a single item.
    T *const       m_itemArray;                          //!< A constant pointer to the array to be used as ring buffer.
    const size_t   m_elementCount;                       //!< Stores the maximum number of items in the ring buffer.
    const size_t   m_elementSize;                        //!< Stores the size of a single data item in the ring buffer, in bytes.
    const size_t   m_arraySize;                          //!< Stores the total size of the array of data items in the ring buffer, in bytes.
    size_t         m_elementsWritten;                    //!< The number of items currently stored in the ring buffer.
    const bool     dynamicAllocation;                    //!< Indicates whether the data array was dynamically allocated.
    T             *m_readPointer;                        //!< Pointer to the current read position in the ring buffer.
    size_t         m_readIndex;                          //!< Index of the current read position in the ring buffer.
    T             *m_writePointer;                       //!< Pointer to the current write position in the ring buffer.
    size_t         m_writeIndex;                         //!< Index of the current write position in the ring buffer.

    /**
     * @brief  Variable storing the overwrite behaviour of the ring buffer
     */
    MEM::ringBufferOverwrite_e m_overwriteSetting;

    /**
     * @brief      Writes a single item to the ringBuffer instance.
     * @param[in]  data
     *             The item to be written.
     * @return     `true` if the write operation was successful, `false` otherwise.
     */
    bool writeSingle(T &data);

    /**
     * @brief      Forces the specified data item to be written to the ring buffer, overwriting the oldest data if necessary.
     * @param[in]  data
     *             The data item to be written to the ring buffer.
     * @return     `true` if the data was successfully written to the ring buffer, `false` otherwise.
     */
    bool overWriteSingle(T &data);

    /**
     * @brief    Populates the function pointers of the ringBuffer instance with the appropriate functions.
     * @details  This function sets the function pointers of the ringBuffer instance to the appropriate functions depending on the
     *           optimization level and execution method chosen.
     */
    void fillFunctionPointers();
  };

  /**
   * @brief    Derived class for a ring buffer with a statically allocated memory.
   * @details  This class is a derived class of `ringBuffer` that takes in a compile-time
   *           assigned piece of memory to be used as a ring buffer. The `elementCount` specifies
   *           the maximum number of elements that can be stored in the ring buffer. The `dataArray`
   *           member is the statically allocated memory used for storing the elements.
   * @tparam   T
   *           Data type of the elements in the ring buffer.
   * @tparam   elementCount
   *           The number of elements that can be stored in the ring buffer.
   */
  template <typename T, const size_t elementCount>
  class staticRingBuffer : public ringBuffer<T>
  {
  public:
    /**
     * @brief Constructor that initializes the `ringBuffer` base class with `elementCount` and `dataArray`.
     */
    staticRingBuffer() : ringBuffer<T>(elementCount, m_dataArray) {};

    /**
     * @brief      Constructor that initializes the `ringBuffer` base class with `elementCount`, `dataArray` and
     *             sets the overwrite behavior of the buffer to either `RINGBUFFER_NO_OVERWRITE` or `RINGBUFFER_ALLOW_OVERWRITE`.
     * @details    This constructor is used to create a statically allocated ring buffer that overwrites the oldest element when
     *             the buffer is full if `overWrite` is set to `RINGBUFFER_ALLOW_OVERWRITE`. If `overWrite` is set to
     *             `RINGBUFFER_NO_OVERWRITE`, new data is not written to the buffer when it is full.
     * @param[in]  overWrite
     *             The overwrite behavior of the buffer. Use `RINGBUFFER_ALLOW_OVERWRITE` to overwrite the oldest element when the buffer is
     *             full, or `RINGBUFFER_NO_OVERWRITE` to prevent writing new data to the buffer when it is full.
     */
    staticRingBuffer(MEM::ringBufferOverwrite_e overWrite) : ringBuffer<T>(elementCount, m_dataArray, overWrite) {};

  private:
    T m_dataArray[elementCount]; //!< Statically allocated memory used as the ring buffer.
  };
} // namespace MEM
/*************************************************************************\
 * Implementation
\*************************************************************************/
namespace MEM
{
  template <typename T>
  ringBuffer<T>::ringBuffer(const size_t elementCount) :
    m_itemArray(new T[elementCount]),
    m_elementCount(elementCount),
    m_elementSize(sizeof(T)),
    m_arraySize(elementCount * sizeof(T)),
    dynamicAllocation(true)
  {
    reset();
    m_overwriteSetting = MEM::RINGBUFFER_NO_OVERWRITE;
    fillFunctionPointers();
  };

  template <typename T>
  ringBuffer<T>::ringBuffer(const size_t elementCount, MEM::ringBufferOverwrite_e overWrite) :
    m_itemArray(new T[elementCount]),
    m_elementCount(elementCount),
    m_elementSize(sizeof(T)),
    m_arraySize(elementCount * sizeof(T)),
    dynamicAllocation(true),
    m_overwriteSetting(overWrite)
  {
    reset();
    fillFunctionPointers();
  };

  template <typename T>
  ringBuffer<T>::ringBuffer(const size_t elementCount, const T *const array) :
    m_itemArray((T *) array),
    m_elementCount(elementCount),
    m_elementSize(sizeof(T)),
    m_arraySize(elementCount * sizeof(T)),
    dynamicAllocation(false)
  {
    reset();
    m_overwriteSetting = MEM::RINGBUFFER_NO_OVERWRITE;
    fillFunctionPointers();
  };

  template <typename T>
  ringBuffer<T>::ringBuffer(const size_t elementCount, const T *const array, MEM::ringBufferOverwrite_e overWrite) :
    m_itemArray((T *) array),
    m_elementCount(elementCount),
    m_elementSize(sizeof(T)),
    m_arraySize(elementCount * sizeof(T)),
    dynamicAllocation(false),
    m_overwriteSetting(overWrite)
  {
    reset();
    fillFunctionPointers();
  };

  template <typename T>
  ringBuffer<T>::~ringBuffer()
  {
    if (dynamicAllocation == true)
    {
      delete[] m_itemArray;
    }
  }

  template <typename T>
  void ringBuffer<T>::setOverwriteBehavior(MEM::ringBufferOverwrite_e overwrite)
  {
    m_overwriteSetting = overwrite;
  }

  template <typename T>
  MEM::ringBufferOverwrite_e ringBuffer<T>::getOverwriteBehavior() const
  {
    return m_overwriteSetting;
  };

  template <typename T>
  void ringBuffer<T>::reset()
  {
    memset(m_itemArray, 0, m_arraySize);
    m_readPointer     = (m_itemArray);
    m_readIndex       = (0);
    m_writePointer    = (m_itemArray);
    m_writeIndex      = (0);
    m_elementsWritten = (0);
  }

  template <typename T>
  bool ringBuffer<T>::ringBufferIsEmpty() const
  {
    return (m_elementsWritten == 0U);
  }

  template <typename T>
  bool ringBuffer<T>::ringBufferIsFull() const
  {
    return m_elementCount == m_elementsWritten;
  }

  template <typename T>
  size_t ringBuffer<T>::ringBufferElementCount() const
  {
    return m_elementCount;
  };

  template <typename T>
  size_t ringBuffer<T>::ringBufferElementSize() const
  {
    return m_elementSize;
  }

  template <typename T>
  size_t ringBuffer<T>::ringBufferSize() const
  {
    return m_arraySize;
  }

  template <typename T>
  size_t ringBuffer<T>::ringBufferElementsWritten() const
  {
    return m_elementsWritten;
  }

  template <typename T>
  bool ringBuffer<T>::write(T &dataRef)
  {
    writeFunctions writeFunction = m_writeFunctionType[m_overwriteSetting];

    return (this->*writeFunction)(dataRef);
  };

  template <typename T>
  bool ringBuffer<T>::write(const T &data)
  {
    T              dataRef       = data;
    writeFunctions writeFunction = m_writeFunctionType[m_overwriteSetting];
    return (this->*writeFunction)(dataRef);
  };

  template <typename T>
  bool ringBuffer<T>::write(T data[], size_t &dataCount)
  {
    writeFunctions writeFunction          = m_writeFunctionType[m_overwriteSetting];
    size_t         dataWrittenSuccesfully = 0;
    size_t         index                  = 0;
    bool           result;

    do
    {
      result = (this->*writeFunction)(*(data + index));
      dataWrittenSuccesfully += result;
      ++index;
    } while ((index < dataCount) && result);
    dataCount = dataWrittenSuccesfully;

    return result;
  };

  template <typename T>
  size_t ringBuffer<T>::write(T data[], const size_t dataCount)
  {
    writeFunctions writeFunction = m_writeFunctionType[m_overwriteSetting];
    size_t         index         = 0;
    bool           result;

    do
    {
      result = (this->*writeFunction)(*(data + index));
      ++index;
    } while ((index < dataCount) && result);

    return index;
  };

  template <typename T>
  bool ringBuffer<T>::read(T &data)
  {
    bool dataAvailable = (m_elementsWritten > 0);

    data                     = *m_readPointer;
    m_itemArray[m_readIndex] = { 0 };
    m_readIndex              = ((m_readIndex + dataAvailable) % m_elementCount);
    m_readPointer            = &m_itemArray[m_readIndex];
    m_elementsWritten -= dataAvailable;

    return dataAvailable;
  };

  template <typename T>
  size_t ringBuffer<T>::read(T data[], const size_t dataRead)
  {
    size_t itemsRead = 0;
    bool   succesfullRead;

    do
    {
      succesfullRead = read(data[itemsRead]);
      itemsRead += succesfullRead;
    } while ((itemsRead < dataRead) && succesfullRead);

    return itemsRead;
  };

  template <typename T>
  bool ringBuffer<T>::peek(T &data, const size_t index)
  {
    bool result = false;
    // Check if the index is within the bounds of the ringbuffer
    if (index < m_elementsWritten)
    {
      // Calculate the location of the element in the array
      size_t arrayIndex = (m_readIndex + index) % m_elementCount;

      // Retrieve the element from the array
      data   = m_itemArray[arrayIndex];
      result = true;
    }
    return result;
  };

  template <typename T>
  T ringBuffer<T>::operator[](const size_t index) const
  {
    T result;
    if (index <= m_elementCount)
    {
      result = m_itemArray[index];
    }
    return result;
  };

  template <typename T>
  bool ringBuffer<T>::writeSingle(T &data)
  {
    bool result = false;
    if (m_elementsWritten < m_elementCount)
    {
      // Write data.
      *m_writePointer = data;
      // Update write index and pointer.
      m_writeIndex   = ((m_writeIndex + 1) % m_elementCount);
      m_writePointer = &m_itemArray[m_writeIndex];
      // Update items written.
      m_elementsWritten = (m_elementsWritten + 1) - (m_elementsWritten >= m_elementCount);
      result            = true;
    }
    return result;
  };

  template <typename T>
  bool ringBuffer<T>::overWriteSingle(T &data)
  {
    // Write data.
    *m_writePointer = data;
    // Update write index and pointer.
    m_writeIndex   = ((m_writeIndex + 1) % m_elementCount);
    m_writePointer = &m_itemArray[m_writeIndex];
    // Update items written.
    ++m_elementsWritten;
    if (m_elementsWritten > m_elementCount)
    {
      // Update read index and pointer
      m_readIndex   = (m_readIndex + 1) % m_elementCount;
      m_readPointer = &m_itemArray[m_readIndex];
      // Correct elements written.
      --m_elementsWritten;
    }
    return true;
  };

  template <typename T>
  void ringBuffer<T>::fillFunctionPointers()
  {
    m_writeFunctionType[MEM::RINGBUFFER_NO_OVERWRITE]    = &ringBuffer<T>::writeSingle;
    m_writeFunctionType[MEM::RINGBUFFER_ALLOW_OVERWRITE] = &ringBuffer<T>::overWriteSingle;
  };
} // namespace MEM
/*************************************************************************\
 * End of file
\*************************************************************************/
