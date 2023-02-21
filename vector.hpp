

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <cstddef>
# include <stdexcept>

namespace ft
{
/*** begin namespace ft ***/
template< class T, class Allocator = std::allocator<T> >
class vector
{
public:
	// typedef so member type names are the same as on cplusplus.com
	typedef T							value_type;
	typedef Alloc						allocator_type;
	typedef T&							reference;
	typedef const T&					const_reference;
	typedef T*							pointer;
	typedef const T*					const_pointer;
	typedef RandIter<T>					iterator;
	typedef RandIter<const T>			const_iterator;
	typedef ReverseRandIter<T>			reverse_iterator;
	typedef ReverseRandIter<const T>	const_reverse_iterator;
	typedef std::ptrdiff_t				difference_type;
	typedef size_t						size_type;
private:
	size_type		_size;
	size_type		_capacity;
	pointer			_array;
	allocator_type	_allocator;
public:
/* ------------------------------ constructors ------------------------------ */
	explicit vector (const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(0), _capacity(0), _array(NULL)
		{ _array = _allocator.allocate(0); }
	explicit vector (size_type n, const value_type& val = value_type()
	, const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(n), _capacity(n), _array(NULL)
	{
		_array = _allocator.allocate(0);
		assign(n, val);
	}
	template <class InputIterator> vector (InputIterator first
	, InputIterator last, const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(0), _capacity(0), _array(NULL)
	{
		_array = _allocator.allocate(0);
		assign<InputIterator>(first, last);
	}
	vector (const vector& x)
		: _allocator(x._allocator), _size(0), _capacity(0), _array(NULL)
	{
		_array = _allocator.allocate(0);
		insert(begin(), x.begin(), x.end());
	}
/* ------------------------------- destructor ------------------------------- */
	~vector ()
	{
		pointer	ptr = _array;
		while (_size > 0)
		{
			_allocator.destroy(ptr);
			ptr ++;
			_size --;
		}
		_allocator.deallocate(_array, capacity());
	}
/* ----------------------------- assign content ----------------------------- */
	vector& operator= (const vector& x)
	{
		if (&x == this)
			return *this;
		clear();
		insert(begin(), x.begin(), x.end());
		return *this;
	}
/* -------------------------------- iterators ------------------------------- */
	iterator				begin()
	{
		return iterator(_array);
	}
	const_iterator			begin() const
	{
		return const_iterator(_array);
	}
	iterator				end()
	{
		return iterator(_array + _size);
	}
	const_iterator			end() const
	{
		return const_iterator(_array + _size);
	}
	reverse_iterator		rbegin()
	{
		return iterator(_array + _size - 1)
	}
	const_reverse_iterator	rbegin() const
	{
		return const_iterator(_array + _size - 1);
	}
	reverse_iterator		rend()
	{
		return iterator(_array - 1);
	}
	const_reverse_iterator	rend() const
	{
		return const_iterator(_array - 1);
	}
/* -------------------------------- capacity -------------------------------- */
	size_type size() const
	{
		return (_size);
	}
	size_type max_size() const
	{
		return (_allocator.max_size());
	}
	void resize (size_type n, value_type val = value_type())
	{
		if (n > _capacity)
			reserve(n);
		while (n > _size)
		{
			_allocator.construct(_size, val);
			_size ++;
		}
		while (n < _size)
		{
			size --;
			_allocator.destroy(_size);
		}
	}
	size_type capacity() const
	{
		return _capacity;
	}
	bool empty() const
	{
		return _size == 0;
	}
	void reserve (size_type n)
	{
		pointer tmp = _allocator.allocate(n);
		for (size_type i = 0; i < _size; i++)
		{
			_allocator.construct(tmp + i, _array[i]);
			_allocator.destroy(_array + i);
		}
		_allocator.deallocate(_array, _capacity);
		_array = tmp;
		_capacity = n;
	}
/* ----------------------------- element access ----------------------------- */
	reference operator[] (size_type n)
	{
		return _array[n];
	}
	const_reference operator[] (size_type n) const
	{
		return _array[n];
	}
	reference at (size_type n)
	{
		if (n >= _size)
		{
			throw std::out_of_range("index out of bounds");
		}
		else
		{
			return _array[n];
		}
	}
	const_reference at (size_type n) const
	{
		if (n >= _size)
		{
			throw std::out_of_range("index out of bounds");
		}
		else
		{
			return _array[n];
		}
	}
	reference front()
	{
		return *begin();
	}
	const_reference front() const
	{
		return *begin();
	}
	reference back()
	{
		return *rbegin();
	}
	const_reference back() const
	{
		return *rbegin();
	}
}
/* ------------------------------- modifiers -------------------------------- */
template <class InputIterator>
void assign (InputIterator first, InputIterator last)
{
	clear();
	insert(begin(), first, last);
}
void assign (size_type n, const value_type& val)
{
	clear();
	insert(begin(), n, val)
}
void push_back (const value_type& val)
{
	if (_size + 1 >= max_size())
	{
		throw std::length_error("vector too big");
	}
	if (_size == _capacity)
		reserve (_capacity + 1);
	_allocator.construct(_array + _size, val);
	_size ++;
}
void pop_back();
{
	_allocator.destroy(_array + _size - 1);
	_size --;
}
iterator insert (iterator position, const value_type& val)
{

}
void insert (iterator position, size_type n, const value_type& val)
{
	if (n == 0) return;
	if (position < begin() || position > end())
	{
		throw std::out_of_range("index out of bounds");
	}
	if (_size + n > capacity)
	{
		reserve(_size + n);
	}
	for (iterator it = rbegin(); it >= position; it--)
	{
		*it = *(it - n);
	}
	for (size_type i = 0; i < n; i++)
	{
		*(position + i) = val;
	}
	_size += n;
}
template <class InputIterator>
void insert (iterator position, InputIterator first, InputIterator last)
{

}

/*** end namespace ft ***/
}
#endif