#pragma once
#include <memory>
#include <stdexcept>
#include "CAllocator.h"
using namespace std;

template <typename TData, class Allocator = CAllocator<TData> >
class CArray
{
public:
  using pointer = typename Allocator::pointer;
  using size_type = typename Allocator::size_type;
  using reference = typename Allocator::reference;
  using const_reference = typename Allocator::const_reference;
  using iterator = pointer;

  CArray()
  {
    m_size = 0;
    m_capacity = 0;
    m_pBuffer = nullptr;
  }

  CArray(
      const CArray & _array
    )
  {
    m_size = _array.m_size;
    m_capacity = _array.m_capacity;
    if (m_capacity)
    {
      m_pBuffer = m_alloc.allocate(m_capacity);
      for (size_type i = 0; i < m_size; ++i)
      {
        m_alloc.construct(m_pBuffer + i, _array.m_pBuffer[i]);
      }
    }
  };

  ~CArray()
  {
    clear();
    m_alloc.deallocate(m_pBuffer, m_capacity);
  };

  void push_back(
      const_reference _value
    )
  {
    if (m_size == m_capacity)
      reserve();
    m_alloc.construct(m_pBuffer + m_size++, _value);
  };

  void insert(
      size_type _index,
      const_reference _value
    )
  {
    if (_index > m_size)
      throw out_of_range("out_of_range");
    if (m_size == m_capacity)
      reserve();
    for (size_type i = ++m_size - 1; i > _index; --i)
    {
      m_alloc.construct(m_pBuffer + i, m_pBuffer[i - 1]);
      m_alloc.destroy(m_pBuffer + (i - 1));
    }
    m_alloc.construct(m_pBuffer + _index, _value);
  };

  void erase(
      size_type _index
    )
  {
    if (_index >= m_size)
      throw out_of_range("out_of_range");
    --m_size;
    if (_index != m_size)
      for (size_type i = _index; i < m_size; ++i)
        m_pBuffer[i] = move(m_pBuffer[i + 1]);
    m_alloc.destroy(m_pBuffer + m_size);
  };

  void clear()
  {
    for (size_type i = 0; i < m_size; ++i)
      m_alloc.destroy(m_pBuffer + (m_size - 1 - i));
    m_size = 0;
  };

  size_type size() const
  {
    return m_size;
  };

  reference operator[](
      size_type _index
    )
  {
    if (_index >= m_size)
      throw out_of_range("out of range");
    return m_pBuffer[_index];
  };

  void reserve()
  {
    size_type newCapacity = m_capacity ? m_capacity * 2 : 1;
    pointer tempBuffer = m_alloc.allocate(newCapacity);
    size_type i;
    try
    {
      for (i = 0; i < m_size; ++i)
        m_alloc.construct(tempBuffer + i, m_pBuffer[i]);
    }
    catch (...)
    {
      for (size_type j = 0; j < i; ++j)
        m_alloc.destroy(tempBuffer + j);
      m_alloc.deallocate(tempBuffer, newCapacity);
      throw;
    }

    for (size_type j = 0; j < m_size; ++j)
      m_alloc.destroy(m_pBuffer + (m_size - 1 - j));

    m_alloc.deallocate(m_pBuffer, m_capacity);
    m_pBuffer = tempBuffer;
    m_capacity = newCapacity;
  };

  iterator begin()
  {
    return &m_pBuffer[0];
  }

  iterator end()
  {
    return &m_pBuffer[m_size];
  }

private:
  size_type m_size;
  size_type m_capacity;
  pointer m_pBuffer;
  Allocator m_alloc;
};
