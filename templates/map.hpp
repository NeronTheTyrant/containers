#ifndef MAP_HPP
# define MAP_HPP

#include "rbtree.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
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
	
		class value_compare {
				friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {};
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				value_compare () : comp() {};
				bool operator() (value_type const & x, value_type const & y) const {
					return comp(x.first, y.first);
				}
		};
		typedef ft::Node<value_type>		Node;
		typedef RBT<value_type, value_compare, Alloc>	tree_type;
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

		//************** Capacity **************//

		bool	empty () const {
			return !size();
		}

		size_type	size () const {
			return _rbtree.size();
		}

		size_type	max_size () const {
			return _alloc.max_size();
		}

		//************** Element Access ************//

		mapped_type &	operator[] (key_type const & k) {
			return (insert(make_pair(k, mapped_type()))).first->second;
		}

		//************ Modifiers *******************//

		ft::pair<iterator, bool>	insert (value_type const & val) {
			iterator	it = find(val.first);
			if (it != end())
				return ft::make_pair(it, false);
			return ft::make_pair(iterator(_rbtree.insertNode(val), _rbtree.root()), true);
		}

		iterator	insert (iterator position, value_type const & val) {
			(void)position;
			iterator	it = find(val.first);
			if (it != end())
				return it;
			return iterator(_rbtree.insertNode(val), _rbtree.root());
		}

	template <class InputIterator>
		void	insert (InputIterator first, InputIterator last) {
			for (; first != last; first++) {
				if (find(first->first) == end())
					_rbtree.insertNode(*first);
			}
		}

		void	erase (iterator position) {
			_rbtree.deleteNode(position);
		}

		size_type	erase (key_type const & k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			else {
				_rbtree.deleteNode(it);
				return 1;
			}
		}

		void	erase (iterator first, iterator last) {
			for (; first != last; first++) {
				_rbtree.deleteNode(first);
			}
		}

		void	swap (map & x) {
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
			return value_compare(_comp);
		}

		//************* Operations *************//

		iterator	find (key_type const & k) {
			Node *	node = _rbtree.root();
			while (node->data.first != k && node != _rbtree.sentinel()) {
				if (_comp(node->data.first, k))
					node = node->right;
				else
					node = node->left;
			}
			if (node == _rbtree.sentinel())
				return end();// not found
			else
				return iterator(node, _rbtree.root());
		}

		const_iterator	find (key_type const & k) const {
			Node *	node = _rbtree.root();
			while (node->data.first != k && node != _rbtree.sentinel()) {
				if (_comp(node->data.first, k))
					node = node->right;
				else
					node = node->left;
			}
			if (node == _rbtree.sentinel())
				return end();// not found
			else
				return const_iterator(node, _rbtree.root());
		}

		size_type	count (key_type const & k) const {
			return (find(k) != end());
		}

		iterator	lower_bound (key_type const & k) {
			iterator it = begin();
			for (iterator ite = end(); it != ite; it++) {
				if (!_comp(it->first, k))
					return it;
			}
			return end();
		}

		const_iterator	lower_bound (key_type const & k) const {
			const_iterator it = begin();
			for (const_iterator ite = end(); it != ite; it++) {
				if (!_comp(it->first, k))
					return it;
			}
			return end();
		}

		iterator	upper_bound (key_type const & k) {
			reverse_iterator it = rbegin();
			for (reverse_iterator ite = rend(); it != ite; it++) {
				if (_comp(it->first, k))
					it.base();
			}
			return end();
		}
		
		const_iterator	upper_bound (key_type const & k) const {
			const_reverse_iterator it = rbegin();
			for (const_reverse_iterator ite = rend(); it != ite; it++) {
				if (_comp(it->first, k))
					it.base();
			}
			return end();
		}

		ft::pair<iterator, iterator>	equal_range (key_type const & k) {
			return make_pair(lower_bound(k), upper_bound(k));
		}

		ft::pair<const_iterator, const_iterator>	equal_range (key_type const & k) const {
			return make_pair(lower_bound(k), upper_bound(k));
		}

		allocator_type	get_allocator () const {
			return _alloc;
		}

};

};

#endif
