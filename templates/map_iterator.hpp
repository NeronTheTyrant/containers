#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

#include "../test.cpp"

namespace ft {

template <class T, class Node = Node<T> >
class tree_iterator {
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

	private:
		Node *	_current;
		Node *	_root;
		Node *	_leaf; // Maybe?
	public:
		tree_iterator () : _current(), _root(), _leaf() {}
		tree_iterator (tree_iterator const & src)
			: _current(src._current), _root(src._root), sentinel(src._leaf) {}
		tree_iterator (Node * current, Node * root)
			: _current(current), _root(root), sentinel(root->parent) {}

		tree_iterator &	operator= (tree_iterator const & rhs) {
			_current = rhs._current;
			_root = rhs._root;
			_leaf = rhs._leaf;
		}

		bool	operator== (tree_iterator const & rhs) {
			return _current == rhs._current;
		}
		bool	operator!= (tree_iterator const & rhs) {
			return !operator==(rhs);
		}
		reference	operator* () {
			return _current->data;
		}
		pointer		operator-> () {
			return &oprator*();
		}
		
		tree_iterator &	operator++ () {
			if (_current->right != _leaf) {
				_current = min(_current->right;
			}
			else if (_current == current->parent->left)
				_current = _current->parent;
			else
				_current = sentinel;
			return *this;
		}

		tree_iterator	operator++ (int) {
			tree_iterator	tmp = *this;
			operator++();
			return tmp;
		}

		tree_iterator &	operator-- () {
			if (current->left != sentinel) {
				_current = max(_current->left);
			}
			else if (_current == current->parent->right)
				_current = current->parent;
			else
				_current = sentinel;
			return *this;
		}

		tree_iterator	operator-- (int) {
			tree_iterator	tmp = *this;
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
class tree_const_iterator {
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
		Node *	_leaf; // Maybe?
	public:
		tree_const_iterator () : _current(), _root(), _leaf() {}
		tree_const_iterator (tree_const_iterator const & src)
			: _current(src._current), _root(src._root), sentinel(src._leaf) {}
		tree_const_iterator (tree_iterator const & src)
			: _current(src._current), _root(src._root), sentinel(src._leaf) {}
		tree_const_iterator (Node * current, Node * root)
			: _current(current), _root(root), sentinel(root->parent) {}

		tree_const_iterator &	operator= (tree_const_iterator const & rhs) {
			_current = rhs._current;
			_root = rhs._root;
			_leaf = rhs._leaf;
		}

		bool	operator== (tree_const_iterator const & rhs) {
			return _current == rhs._current;
		}
		bool	operator!= (tree_const_iterator const & rhs) {
			return !operator==(rhs);
		}
		reference	operator* () {
			return _current->data;
		}
		pointer		operator-> () {
			return &oprator*();
		}
		
		tree_const_iterator &	operator++ () {
			if (_current->right != _leaf) {
				_current = min(_current->right;
			}
			else if (_current == current->parent->left)
				_current = _current->parent;
			else
				_current = sentinel;
			return *this;
		}

		tree_const_iterator	operator++ (int) {
			tree_const_iterator	tmp = *this;
			operator++();
			return tmp;
		}

		tree_const_iterator &	operator-- () {
			if (current->left != sentinel) {
				_current = max(_current->left);
			}
			else if (_current == current->parent->right)
				_current = current->parent;
			else
				_current = sentinel;
			return *this;
		}

		tree_const_iterator	operator-- (int) {
			tree_const_iterator	tmp = *this;
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
