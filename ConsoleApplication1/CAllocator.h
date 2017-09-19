#pragma once
using namespace std;

template <class T>
class CAllocator{
public:
	using value_type = T;
	using size_type = size_t;
	using pointer = T *;
  using reference = value_type &;
  using const_reference = const value_type &;

  CAllocator() noexcept
  {};

	template <class U> CAllocator(
      const CAllocator<U>&
    ) noexcept
  {};

  template <class U>
  constexpr bool operator== (
      const CAllocator<U>&
    ) noexcept
  {
    return true;
  };

  template <class U>
  constexpr bool operator!= (
     const CAllocator<U>&
    ) noexcept
  {
    return false;
  };

	pointer allocate(
      size_t n
    )
	{
		if (n == 0)
		{
			return nullptr;
		}
    void* ptr = malloc(n * sizeof(T));
    if (!ptr)
      throw bad_alloc();
		return static_cast<pointer>(ptr);
	};

	void deallocate(
      pointer p,
      size_t n
    )
	{
		free(p);
	};

  void construct(
      pointer p,
      const_reference val
    )
  {
    new (p) T(val);
  }

  void destroy(
      pointer p
    )
  {
    p->~T();
  }
};

