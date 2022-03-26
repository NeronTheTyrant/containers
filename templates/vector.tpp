#ifndef VECTOR_TPP
# define VECTOR_TPP

#include <iterator>
#include "reverse_iterator.tpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include <limits.h>

template <typename T, class A = std::allocator<T> >
class vector {
	public:
		/******************** typedefs *************************/
		typedef				A					allocator_type;
		typedef typename	A::value_type		value_type;
		typedef typename	A::pointer			pointer;
		typedef typename	A::const_pointer	const_pointer;
		typedef typename	A::reference		reference;
		typedef typename	A::const_reference	const_reference;
		typedef typename	A::size_type		size_type;
		typedef typename	A::difference_type	difference_type;

	private:
		/******************** attributes *************************/
		value_type *	_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
		class iterator {
			public:
				/******************** typedefs *************************/
				typedef typename A::value_type			value_type;
				typedef typename A::difference_type		difference_type;
				typedef typename A::reference			reference;
				typedef typename A::pointer				pointer;
				typedef std::random_access_iterator_tag	iterator_category;

			private:
				/******************** attributes *************************/
				value_type *	_ptr;

			public:
				/************** Constructors / Destructors *****************/
				iterator	() : _ptr(NULL) {};
				iterator	(iterator const & copy) {*this = copy;};
				iterator	(value_type * ptr) : _ptr(ptr) {};
				~iterator	() {};

				/************** Operator Overloads *****************/
				iterator &	operator=	(iterator const & rhs)	{_ptr = rhs._ptr;};
				bool		operator==	(iterator const & rhs)	{return _ptr == rhs._ptr ? true : false;};
				bool		operator!=	(iterator const & rhs)	{return !operator==(rhs);};
				bool		operator<	(iterator const & rhs)	{return _ptr < rhs._ptr ? true : false;};
				bool		operator>	(iterator const & rhs)	{return !operator<(rhs);};
				bool		operator<=	(iterator const & rhs)	{return operator==(rhs) || operator<(rhs);};
				bool		operator>=	(iterator const & rhs)	{return operator==(rhs) || operator>(rhs);};

				iterator &	operator++	()				{++_ptr; return *this;};
				iterator	operator++	(int)			{return iterator(_ptr + 1);};
				iterator &	operator--	()				{--_ptr; return *this;};
				iterator	operator--	(int)			{return iterator(_ptr - 1);};
				iterator	operator+	(size_type n)	{return iterator(_ptr + n);};
				friend iterator operator+ (size_type n, iterator const & rhs);
				iterator &	operator+=	(size_type n)	{_ptr += n; return *this;};
				iterator	operator-	(size_type n)	{return iterator(_ptr - n);};
				iterator &	operator-=	(size_type n)	{_ptr -= n; return *this;};
				difference_type operator- (iterator const & rhs) {return (_ptr - rhs._ptr);};

				reference	operator*	()				{return	*_ptr;};
				pointer		operator->	()				{return _ptr;};
				reference	operator[]	(size_type n)	{return *(_ptr + n);};
				
				/************** Member functions *****************/
				value_type *	ptr () {return _ptr;};
		};

		class const_iterator {
			public:
				/******************** typedefs *************************/
				typedef typename const A::value_type	value_type;
				typedef typename A::difference_type		difference_type;
				typedef typename const A::reference		reference;
				typedef typename const A::pointer		pointer;
				typedef std::random_access_iterator_tag	iterator_category;

			private:
				value_type *	_ptr;

			public:
				/************** Constructors / Destructors *****************/
				const_iterator	() : _ptr(NULL) {};
				const_iterator	(const_iterator const & copy) _ptr(copy._rhs) {};
				const_iterator	(iterator const & copy) : _ptr(copy.ptr()) {};
				const_iterator	(value_type * ptr) : _ptr(ptr) {};
				~const_iterator	() {};

				/************** Operator Overloads *****************/
				const_iterator &	operator=	(const_iterator const & rhs)	{_ptr = rhs._ptr;};
				bool				operator==	(const_iterator const & rhs)	{return _ptr == rhs._ptr ? true : false;};
				bool				operator!=	(const_iterator const & rhs)	{return !operator==(rhs);};
				bool				operator<	(const_iterator const & rhs)	{return _ptr < rhs._ptr ? true : false;};
				bool				operator>	(const_iterator const & rhs)	{return !operator<(rhs);};
				bool				operator<=	(const_iterator const & rhs)	{return operator==(rhs) || operator<(rhs);};
				bool				operator>=	(const_iterator const & rhs)	{return operator==(rhs) || operator>(rhs);};

				const_iterator &	operator++	()							{++_ptr; return *this;};
				const_iterator		operator++	(int)						{return const_iterator(_ptr + 1);};
				const_iterator &	operator--	()							{--_ptr; return *this;};
				const_iterator		operator--	(int)						{return const_iterator(_ptr - 1);};
				const_iterator		operator+	(size_type n)				{return const_iterator(_ptr + n);};
				friend const_iterator operator+ (size_type n, const_iterator const & rhs);
				const_iterator &	operator+=	(size_type n)				{_ptr += n; return *this;};
				const_iterator		operator-	(size_type n)				{return const_iterator(_ptr - n);};
				const_iterator &	operator-=	(size_type n)				{_ptr -= n; return *this;};
				difference_type		operator- (const_iterator const & rhs)	{return (_ptr - rhs._ptr);};

				reference	operator*	()									{return	*_ptr;};
				pointer		operator->	()									{return _ptr;};
				reference	operator[]	(size_type n)						{return *(_ptr + n);};
		};

		/************** Constructors / Destructors *****************/
		explicit vector (allocator_type const & alloc = allocator_type())
			: _array(NULL), _capacity(0), _size(0), _alloc(alloc) {};
		
		explicit vector (size_type n, value_type const & val = value_type(), 
			allocator_type const & alloc = allocator_type())
			: _array(NULL), _capacity(n), _size(n), _alloc(alloc) {
			_array = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_array + i, val);
		};

	template <class InputIterator>
		vector (InputIterator first, InputIterator last,
			allocator_type const & alloc = allocator_type())
			: _array(NULL), _capacity(0), _size(0), _alloc(alloc) {
			_size = std::distance(first, last);
			_capacity = _size;
			_array = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(_array + i, *first);
				first++;
			}
		};

		vector (vector const & x)
			: _array(NULL), _size(x._size), _capacity(x._capacity), _alloc(x._alloc) {
			_array = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_array + i, x._array[i]);
		};

		~vector () {
			this->clear();
			_alloc.deallocate(_array, _capacity);
		};

		vector & operator= (vector const & x) {
			if (this == &x)
				return *this;
			this->clear();
			_alloc.deallocate(_array, _capacity);
			_size = x._size;
			_capacity = x._capacity;
			_array = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_array + i, x._array[i];
			return *this;
		};

		/**************** Iterators ********************/

					  iterator begin ()			{return iterator(_array);};
				const_iterator begin () const	{return const_iterator(_array);} ;
					  iterator end ()			{return iterator(_array + _size);};
				const_iterator end () const		{return const_iterator(_array + _size);};
			  reverse_iterator rbegin ()		{return reverse_iterator(end());};
		const_reverse_iterator rbegin () const	{return const_reverse_iterator(end);
			  reverse_iterator rend ()			{return reverse_iterator(begin());};
		const_reverse_iterator rend () const	{return const_reverse_iterator(begin());};

		/**************** Capacity ********************/

		size_type	size() const		{return _size;};
		size_type	max_size() const	{return _alloc.max_size;};
		size_type	capacity() const	{return _capacity;};
		bool		empty() const		{return !(_size);};

		void		resize (size_type n, value_type val = value_type()) {
			if (n == _size)
				return;
			if (n > _capacity)
				reserve(n);
			if (n < _size) {
				for (size_type i = n; n < _size; i++)
					_alloc.destroy(_array + i);
			}
			if (n > _size) {
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_array + i, val);
			}
			_size = n;
		}

		void		reserve(size_type n) {
			if (n <= capacity())
				return ;
			value_type *	_temp;
			_temp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_temp + i, _array[i]);
			this->clear();
			_alloc.deallocate(_array, _capacity);
			_array = _temp;
			_capacity = n;
		}

		/**************** Element Access ********************/

			  reference	operator[] (size_type n) {return _array[n];};
		const_reference	operator[] (size_type n) const {return _array[n];}
			  reference	at (size_type n) {
					if (n >= _size)
						throw std::out_of_range();
					return _array[n];
				};
		const_reference	at (size_type n) const {
					if (n >= _size)
						throw std::out_of_range();
					return _array[n];
				};
			  reference	front()			{return _array[0];};
		const_reference	front() const	{return _array[0];};
			  reference	back()			{return *rbegin();};
		const_reference	back() const	{return *rbegin();};

		/**************** Modifiers ********************/
	template <class InputIterator>
		void	assign (InputIterator first, InputIterator last) {
			clear();
			size_type n = std::distance(first, last);
			if (n > _capacity)
				reserve(n);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_array + i, *first);
				first++;
			}
			_size = n;
		}

		void	assign (size_type n, value_type const & val) {
			clear();
			if (n > _capacity)
				reserve(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_array + i, val);
			_size = n;
		}

		void	push_back (value_type const & val) {
			if (_size == _capacity)
				reserve(_capacity * 2);
			_alloc.construct(_array + _size, val);
			_size += 1;
		}

		void	pop_back () {
			_alloc.destroy(_array + (_size - 1));
		}

		iterator	insert (iterator position, value_type const & val) { //single Element
			size_type	dist = std::distance(_array, position);
			if (_size == _capacity) {
				reserve((_capacity ? _capacity * 2 : 1));
				position = begin() + dist;
			}
			if (position != end()) {
				for (iterator it = end() - 1; it != position; it--) {
					_alloc.construct((it + 1).ptr(), *it);
					_alloc.destroy(it.ptr());
				}
			}
			_alloc.construct((position).ptr(), val);
			_size++;
			return (position);
		}

		void	insert (iterator position, size_type n, value_type const & val) {
			size_type	dist = std::distance(_array, position);
			if (n > _capacity - _size) {
				if (n <= (_capacity * 2) - _size)
					reserve(_capacity * 2);
				else
					reserve(_size + n);
				position = begin() + dist;
			}
			if (position != end()) {
				for (iterator it = end() - 1; it != position; it--) {
					_alloc.construct((it + n).ptr(), *it);
					_alloc.destroy(it.ptr());
				}
			}
			for (size_type i = dist; i < n; i++)
				_alloc.construct((position + i).ptr(), val);
			_size += n;
		}

	template <class InputIterator>
		void	insert (iterator position, InputIterator first, InputIterator last) {
			size_type	dist = std::distance(_array, position);
			size_type	count = std::distance(first, last);
			if (count > _capacity - _size) {
				if (count <= (_capacity * 2) - _size)
					reserve(_capacity * 2);
				else
					reserve(_size + count);
				position = begin() + dist;
			}
			if (position != end()) {
				for (iterator it = end() - 1; it != position; it--) {
					_alloc.construct((it + count).ptr(), *it);
					_alloc.destroy(it.ptr());
				}
			}
			for (size_type i = dist; i < count; i++)
				_alloc.construct((position + i).ptr(), *(first + i));
			_size += count;
		}

		iterator	erase (iterator position) {
			_alloc.destroy(position.ptr());
			size_type dist = std::distance(begin(), position);
			iterator ite = end();
			for (iterator it = position + 1; it != ite; it++) {
				_alloc.construct((it - 1).ptr(), *it);
				_alloc.destroy(it.ptr());
			}
			_size -= 1;
			return (position);
		}

		iterator	erase (iterator first, iterator last) {
			size_type dist = std::distance(begin(), first);
			size_type count = std::distance(first, last);
			for (iterator it = first; it != last; it++)
				_alloc.destroy(it.ptr());
			iterator ite = end();
			for (iterator it = last + 1; it != ite; it++) {
				_alloc.construct((it - count).ptr(), *it);
				_alloc.destroy(it.ptr());
			}
			_size -= count;
			return (first);
		}

		void	swap (vector & x) {
			pointer	tmp_arr = _array;
			size_type	tmp_size = _size;
			size_type	tmp_cap = _capacity;
			allocator_type	tmp_alloc = _alloc;

			_array = x._array;
			_size = x._size;
			_capacity = x._capacity;
			_alloc = x._alloc;

			x._array = tmp_arr;
			x._size = tmp_size;
			x._capacity = tmp_cap;
			x._alloc = tmp_alloc;
		}

		void	clear () {
		iterator ite = end();
		for (iterator it = begin(); it != ite; it++)
			_alloc.destroy(it.ptr());
		_size = 0;
		}

		allocator_type	get_allocator () const {return _alloc;};
};

template <class T, class Alloc>
bool operator== (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!= (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator< (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<= (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator> (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>= (vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
	x.swap(y);
}

#endif
