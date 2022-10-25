

#ifndef VECTOR_HPP
# define VECTOR_HPP
namespace ft
{
/* begin namespace ft */
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
	/** constructors **/
	explicit vector (const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(0), _capacity(0), _container(NULL)
		{};
	explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	vector (const vector& x);
	/** destructors **/
}
/* end namespace ft */
}
#endif