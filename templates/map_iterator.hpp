#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

namespace ft {

template <class T>
class map_iterator {
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Node<T>							Node

	private:
		Node *	_current;
		Node *	_root;
		Node *	_sentinel; // Maybe?
	public:
		map_iterator () : _current(), _root(), _sentinel() {}
		map_iterator (map_iterator const & src)
			: _current(src._current), _root(src._root), sentinel(src._sentinel) {}
		map_iterator (Node * current, Node * root)
			: _current(current), _root(root), sentinel(root->parent) {}

		map_iterator &	operator= (map_iterator const & rhs) {
			_current = rhs._current;
			_root = rhs._root;
			_sentinel = rhs._sentinel;
		}

		bool	operator== (map_iterator const & rhs) {
			return _current == rhs._current;
		}
		bool	operator!= (map_iterator const & rhs) {
			return !operator==(rhs);
		}
		reference	operator* () {
			return _current->data;
		}
		pointer		operator-> () {
			return &oprator*();
		}
		
		map_iterator &	operator++ () {
			if (_current->right != _sentinel) {
				_current = min(_current->right;
			}
			else if (_current == current->parent->left)
				_current = _current->parent;
			else
				_current = sentinel;
			return *this;
		}

		map_iterator	operator++ (int) {
			map_iterator	tmp = *this;
			operator++();
			return tmp;
		}

		map_iterator &	operator-- () {
			if (current->left != sentinel) {
				_current = max(_current->left);
			}
			else if (_current == current->parent->right)
				_current = current->parent;
			else
				_current = sentinel;
			return *this;
		}

		map_iterator	operator-- (int) {
			map_iterator	tmp = *this;
			operator--();
			return tmp;
		}

		Node *	min (Node *node) {
			while (node->left != sentinel)
				node = node->left;
			return node;
		}

		Node *	max (Node *node) {
			while (node->right != sentinel)
				node = node->right;
			return node;
		}
};

template <class T>
class map_const_iterator {
	public:
		typedef T const							value_type;
		typedef T const *						pointer;
		typedef T const &						reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Node<T>							Node

	private:
		Node *	_current;
		Node *	_root;
		Node *	_sentinel; // Maybe?
	public:
		map_const_iterator () : _current(), _root(), _sentinel() {}
		map_const_iterator (map_const_iterator const & src)
			: _current(src._current), _root(src._root), sentinel(src._sentinel) {}
		map_const_iterator (map_iterator const & src)
			: _current(src._current), _root(src._root), sentinel(src._sentinel) {}
		map_const_iterator (Node * current, Node * root)
			: _current(current), _root(root), sentinel(root->parent) {}

		map_const_iterator &	operator= (map_const_iterator const & rhs) {
			_current = rhs._current;
			_root = rhs._root;
			_sentinel = rhs._sentinel;
		}

		bool	operator== (map_const_iterator const & rhs) {
			return _current == rhs._current;
		}
		bool	operator!= (map_const_iterator const & rhs) {
			return !operator==(rhs);
		}
		reference	operator* () {
			return _current->data;
		}
		pointer		operator-> () {
			return &oprator*();
		}
		
		map_const_iterator &	operator++ () {
			if (_current->right != _sentinel) {
				_current = min(_current->right;
			}
			else if (_current == current->parent->left)
				_current = _current->parent;
			else
				_current = sentinel;
			return *this;
		}

		map_const_iterator	operator++ (int) {
			map_const_iterator	tmp = *this;
			operator++();
			return tmp;
		}

		map_const_iterator &	operator-- () {
			if (current->left != sentinel) {
				_current = max(_current->left);
			}
			else if (_current == current->parent->right)
				_current = current->parent;
			else
				_current = sentinel;
			return *this;
		}

		map_const_iterator	operator-- (int) {
			map_const_iterator	tmp = *this;
			operator--();
			return tmp;
		}

		Node *	min (Node *node) {
			while (node->left != sentinel)
				node = node->left;
			return node;
		}

		Node *	max (Node *node) {
			while (node->right != sentinel)
				node = node->right;
			return node;
		}
};
