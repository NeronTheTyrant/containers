#ifndef MAP_HPP
# define MAP_HPP

#include "map_iterator.hpp"

namespace ft {

template <class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> >
class map {

	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::difference_type			difference_type;
		typedef typename Alloc::size_type				size_type;
		typedef RBT<value_type, value_compare>			tree_type;
	
	template <class Key, class T, class Compare, class Alloc>
		class map<Key, T, Compare, Alloc>::value_compare {
				friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {};
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (value_type const & x, value_type const & y) const {
					return comp(x.first, y.first);
				}
		};
	protected:
		tree_type		_rbtree;
		allocator_type	_alloc;
		key_compare		_comp;
	public:
		explicit map (key_compare const & comp = key_compare(),
		allocator_type const & alloc = allocator_type())
		: _rbtree(), _alloc(alloc), _comp(comp) {}
	template <class InputIterator>
		map (InputIterator first, InputIterator last,
		key_compare const & comp = key_compare(),
		allocator_type const & alloc = allocator_type())
		: _rbtree(), _alloc(alloc), _comp(comp) {
			insert(first, last);
		}
		map (map const & x)
		: _rbtree(x._rbtree), _alloc(x._alloc), _comp(x._comp) {}

		~map () {}

		map &	operator= (map const & rhs) {
			this->_rbtree = rhs._rbtree;
			return *this;
		}

		typedef typename tree_type::iterator		iterator;
		typedef typename tree_type::const_iterator	const_iterator;

		iterator	begin () {
			return _rbtree.begin();
		}

		const_iterator	begin () const {
			return _rbtree.begin();
		}

		iterator	end() {
			return _rbtree.end();
		}

		const_iterator	end() const {
			return _rbtree.end();
		}

		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		reverse_iterator	rbegin () {
			return reverse_iterator(_rbtree.end());
		}

		const_reverse_iterator	rbegin () const {
			return const_reverse_iterator(_rbtree.end());
		}

		reverse_iterator	rend () {
			return reverse_iterator(_rbtree.begin());
		}

		const_reverse_iterator	rend () const {
			return const_reverse_iterator(_rbtree.begin());
		}




};

#endif
