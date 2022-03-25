template <class Iterator>
class reverse_iterator {
	public:
		typedef Iterator							iterator_type;
		typedef iterator_traits<Iterator>			traits;
		typedef typename traits::iterator_category	iterator_category;
		typedef typename traits::value_type			value_type;
		typedef typename traits::difference_type	difference_type;
		typedef typename traits::pointer			pointer;
		typedef typename traits::reference			reference;

		reverse_iterator () : _base(iterator_type()) {};
		explicit reverse_iterator (iterator_type it) : _base(it) {};
	template <class Iter>
		reverse_iterator (reverse_iterator<Iter> const & rev_it) : _base(rev_it.base()) {};

		~reverse_iterator () {};
		//virtual? why?

		iterator_type base () const {return _base;};

		/********* Operator Overloads ***********/
		reference			operator*	() const					{return *(_base - 1);};
		reverse_iterator	operator+	(difference_type n) const	{return reverse_iterator(_base - n);};
		reverse_iterator &	operator++	()							{_base--; return *this;};
		reverse_iterator	operator++	(int)						{reverse_iterator temp = *this; ++(*this); return temp;};
		reverse_iterator &	operator+=	(difference_type n)			{_base -= n; return *this;};
		reverse_iterator	operator-	(difference_type n) const	{return reverse_iterator(_base + n);};
		reverse_iterator &	operator--	()							{_base++; return *this;};
		reverse_iterator	operator--	(int)						{reverse_iterator temp = *this; --(*this); return temp;};
		reverse_iterator &	operator-=	(difference_type n)			{_base += n; return *this;};
		pointer				operator->	() const					{return &(operator*());};
		reference			operator[]	(difference_type n)			{return base()[-n -1];};

	private:
		iterator_type	_base;
};

template <class Iterator>
bool	operator== (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator const & rhs) {
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool	operator!= (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator const & rhs) {
	return lhs.base() != rhs.base();
}

template <class Iterator>
bool	operator< (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator const & rhs) {
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool	operator<= (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator const & rhs) {
	return lhs.base() >= rhs.base();
}

template <class Iterator>
bool	operator> (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator const & rhs) {
	return lhs.base() < rhs.base();
}

template <class Iterator>
bool	operator>= (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator const & rhs) {
	return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator>	operator+ (typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const & rev_it) {
	return rev_it + n;
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator> const & rhs) {
	return rhs.base() - lhs.base();
}