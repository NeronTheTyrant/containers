#ifndef SET_HPP
# define SET_HPP

#include "rbtree.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft {

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class set {

	public:
		typedef T										key_type;
		typedef T										value_type;
		typedef Compare									key_compare;
		typedef Compare									value_compare;
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::difference_type			difference_type;
		typedef typename Alloc::size_type				size_type;
		typedef ft::Node<value_type>		Node;
		typedef RBT<value_type, key_compare, Alloc>	tree_type;
	protected:
		tree_type		_rbtree;
		allocator_type	_alloc;
		key_compare		_comp;
	public:
		explicit set (key_compare const & comp = key_compare(),
		allocator_type const & alloc = allocator_type())
		: _rbtree(), _alloc(alloc), _comp(comp) {}
	template <class InputIterator>
		set (InputIterator first, InputIterator last,
		key_compare const & comp = key_compare(),
		allocator_type const & alloc = allocator_type())
		: _rbtree(), _alloc(alloc), _comp(comp) {
			insert(first, last);
		}
		set (set const & x)
		: _rbtree(x._rbtree), _alloc(x._alloc), _comp(x._comp) {}

		~set () {}

		set &	operator= (set const & rhs) {
			this->_rbtree = rhs._rbtree;
			return *this;
		}

		typedef typename tree_type::const_iterator	iterator;
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

		//************** Capacity **************//

		bool	empty () const {
			return !size();
		}

		size_type	size () const {
			return _rbtree.size();
		}

		size_type	max_size () const {
			std::allocator<Node>	tmp;
			return tmp.max_size();
		}

		//************ Modifiers *******************//

		ft::pair<iterator, bool>	insert (value_type const & val) {
			iterator	it = find(val);
			if (it != end())
				return ft::make_pair(it, false);
			return ft::make_pair(iterator(_rbtree.insertNode(val), _rbtree.root()), true);
		}

		iterator	insert (iterator position, value_type const & val) {
			(void)position;
			iterator	it = find(val);
			if (it != end())
				return it;
			return iterator(_rbtree.insertNode(val), _rbtree.root());
		}

	template <class InputIterator>
		void	insert (InputIterator first, InputIterator last) {
			for (; first != last; first++) {
				if (find(*first) == end())
					_rbtree.insertNode(*first);
			}
		}

		void	erase (iterator position) {
			_rbtree.deleteNode(position);
		}

		size_type	erase (value_type const & k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			else {
				_rbtree.deleteNode(it);
				return 1;
			}
		}

		void	erase (iterator first, iterator last) {
			iterator tmp;
			while (first != last) {
				tmp = first;
				first++;
				erase(tmp);
			}
		}

		void	swap (set & x) {
			Node *	root_tmp = _rbtree.root();
			Node *	sent_temp = _rbtree.sentinel();
			size_type	size_temp = _rbtree.size();

			_rbtree.setRoot(x._rbtree.root());
			_rbtree.setSentinel(x._rbtree.sentinel());
			_rbtree.setSize(x._rbtree.size());

			x._rbtree.setRoot(root_tmp);
			x._rbtree.setSentinel(sent_temp);
			x._rbtree.setSize(size_temp);
		}

		void	clear () {
			_rbtree.clear();
		}

		//************** Observers *****************//

		key_compare	key_comp () const {
			return _comp;
		}

		value_compare	value_comp () const {
			return _comp;
		}

		//************* Operations *************//
		iterator	find (key_type const & k) const {
			Node *	node = _rbtree.root();
			while (node->data != k && node != _rbtree.sentinel()) {
				if (_comp(node->data, k))
					node = node->right;
				else
					node = node->left;
			}
			if (node == _rbtree.sentinel())
				return end();// not found
			else
				return iterator(node, _rbtree.root());
		}

		size_type	count (key_type const & k) const {
			return (find(k) != end());
		}

		iterator	lower_bound (key_type const & k) const {
			iterator it = begin();
			for (iterator ite = end(); it != ite; it++) {
				if (*it == k || !_comp(*it, k))
					return it;
			}
			return end();
		}

		iterator	upper_bound (key_type const & k) const {
			iterator it = begin();
			for (iterator ite = end(); it != ite; it++) {
				if (*it != k && !_comp(*it, k))
					return it;
			}
			return end();
		}

		ft::pair<iterator, iterator>	equal_range (key_type const & k) const {
			return make_pair(lower_bound(k), upper_bound(k));
		}

		allocator_type	get_allocator () const {
			return _alloc;
		}

};

template <class T, class Compare, class Alloc>
bool operator== (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Compare, class Alloc>
bool operator!= (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs) {
	return !(lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool operator< (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs) {
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Compare, class Alloc>
bool operator> (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs) {
	return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator<= (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs) {
	return !(rhs < lhs);
}

template <class T, class Compare, class Alloc>
bool operator>= (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs) {
	return !(lhs < rhs);
}

template <class T, class Compare, class Alloc>
void swap (set<T, Compare, Alloc> const & x,
			set<T, Compare, Alloc> const & y) {
	x.swap(y);
}

};

#endif
