#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
	public:
		typedef T							value_type;
		typedef Container					container_type;
		typedef typename container_type::size_type	size_type;
	protected:
		container_type	c;
	public:
		explicit	stack (container_type const & cntr = container_type())
			: c(cntr) {}

		bool	empty () const {
			return c.empty();
		}

		size_type	size () const {
			return c.size();
		}

		value_type &	top () {
			return c.back();
		}

		value_type const &	top () const {
			return c.back();
		}

		void	push (value_type const & val) {
			c.push_back(val);
		}

		void	pop () {
			c.pop_back();
		}

		friend bool operator== (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
			return rhs.c == lhs.c;
		}
		friend bool operator!= (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
			return rhs.c != lhs.c;
		}
		friend bool operator< (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
			return rhs.c < lhs.c;
		}
		friend bool operator<= (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
			return rhs.c <= lhs.c;
		}
		friend bool operator> (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
			return rhs.c > lhs.c;
		}
		friend bool operator>= (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
			return rhs.c >= lhs.c;
		}
};
/*
template <class T, class Container>
bool operator== (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
	return rhs.c == lhs.c;
}

template <class T, class Container>
bool operator!= (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
	return rhs.c != lhs.c;
}

template <class T, class Container>
bool operator< (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
	return rhs.c < lhs.c;
}

template <class T, class Container>
bool operator<= (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
	return rhs.c <= lhs.c;
}

template <class T, class Container>
bool operator> (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
	return rhs.c > lhs.c;
}

template <class T, class Container>
bool operator>= (stack<T, Container> const & rhs, stack<T, Container> const & lhs) {
	return rhs.c >= lhs.c;
}
*/
};

#endif
