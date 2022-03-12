#ifndef VECTOR_TPP
# define VECTOR_TPP

#include <iterator>

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
		T *	_array;
		size_t	_size;
		size_t	_capacity;
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


};

#endif
