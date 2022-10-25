

#ifndef VECTOR_HPP
# define VECTOR_HPP
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
		: _allocator(alloc), _size(0), _capacity(0), _container(NULL)
		{ _array = _allocator.allocate(0); }
	explicit vector (size_type n, const value_type& val = value_type()
	, const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(0), _capacity(0), _container(NULL)
	{
		_array = _allocator.allocate(0);
		assign(n, val);
	}
	template <class InputIterator> vector (InputIterator first
	, InputIterator last, const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(0), _capacity(0), _container(NULL)
	{
		_array = _allocator.allocate(0);
		assign<InputIterator>(begin, end);
	}
	vector (const vector& x)
		: _allocator(alloc), _size(0), _capacity(0), _container(NULL)
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
			size --;
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
		return (_capacity);
	}
	bool empty() const
	{
		return (_size == 0);
	}
	void reserve (size_type n)
	{
		pointer tmp = _allocator.allocate(n);
		for (size_type i = 0; i < _size, i++)
		{
			_allocator.construct(tmp + i, _array[i]);
			_allocator.destroy(_array + i);
		}
		_allocator.deallocate(_array, _capacity);
		_array = tmp;
		_capacity = n;
	}
/* ----------------------------- element access ----------------------------- */
 
}
/*** end namespace ft ***/
}
#endif