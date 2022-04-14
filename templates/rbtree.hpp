#ifndef RBTREE_HPP
# define RBTREE_HPP
#include "../temp.hpp"
#include "tree_iterator.hpp"

namespace ft {



/*
template <typename T>
class Node {
	public:
		typedef T	value_type;

		value_type	data;
		Node *		parent;
		Node *		left;
		Node *		right;
		bool		color; // 0 is black, 1 is red

		Node() : parent(NULL), left(NULL), right(NULL) {};
		Node(Node const & src) : parent(src.parent), left(src.left), right(src.left), color(src.color) {};
		~Node() {};

		Node &	operator= (Node const & rhs) {
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			color = rhs.color;
			return *this;
		};
};
*/
template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class RBT {
	public:
		typedef T							value_type;
		typedef Compare						key_compare;
		typedef ft::Node<value_type>		Node;
		typedef Alloc						allocator_type;
		typedef std::allocator<Node>		node_allocator_type;
		typedef typename Alloc::size_type	size_type;

		typedef tree_iterator<T>		iterator;
		typedef tree_const_iterator<T>	const_iterator;

		Node *				_root;
		Node *				_sentinel; // leaf
		size_type			_size;
		allocator_type		_alloc;
		node_allocator_type	_nodeAlloc;
		key_compare			_comp;
	protected:
//		#define BLACK	0
//		#define RED		1
	public:
		RBT(key_compare const & compare = key_compare(),
			allocator_type const & allocator = allocator_type())
			: _root(NULL), _sentinel(NULL), _alloc(allocator), _nodeAlloc(node_allocator_type()),
			  _comp(compare) {
			initSentinel();
			_root = _sentinel;
			_size = 0;
		};

		RBT (RBT const & src)
			: _root(NULL), _sentinel(NULL), _alloc(src._alloc), _nodeAlloc(src._nodeAlloc), 
			  _comp(src._comp) {
			initSentinel();
			_root = _sentinel;
			_size = 0;
			*this = src;
		}

		~RBT () {
			clear();
			_nodeAlloc.destroy(_sentinel);
			_nodeAlloc.deallocate(_sentinel, 1);
		}

		RBT &	operator= (RBT const & rhs) {
			clear();
			const_iterator ite = rhs.end();
			for (const_iterator it = rhs.begin(); it != ite; it++)
				insertNode(*it);
			_size = rhs._size;
			return *this;
		}

		void	clear () {
			clearHelper(_root);
			_size = 0;
			_root = _sentinel;
		}

		iterator begin () {
			return iterator(minimum(this->_root), _root);
		}
		
		const_iterator begin () const {
			return const_iterator(minimum(this->_root), _root);
		}

		iterator end () {
			return iterator(_sentinel, _root);
		}

		const_iterator end () const {
			return const_iterator(_sentinel, _root);
		}

		size_type	size () const {
			return this->_size;
		}

		Node *	root () const {
			return this->_root;
		}

		Node *	sentinel () const {
			return this->_sentinel;
		}

		void	setSize (size_type size) {
			_size = size;
		}

		void	setRoot (Node * root) {
			_root = root;
		}

		void	setSentinel (Node * sentinel) {
			_sentinel = sentinel;
		}

		Node *	minimum(Node * node) const {
			while (node->left != _sentinel)
				node = node->left;
			return node;
		}

		Node *	maximum(Node * node) const {
			while (node->right != _sentinel)
				node = node->right;
			return node;
		}

		Node *	insertNode(value_type const & val) {
			return insertNodeHelper(val);
		}

		void deleteNode(Node * z) {
			deleteNodeHelper(z);
		}

		void deleteNode(iterator it) {
			deleteNodeHelper(it.getCurrent());
		}


	private:
		void	initSentinel() {
			_sentinel = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(_sentinel, Node());
			_alloc.construct(&_sentinel->data, value_type());
			_sentinel->parent = NULL;
			_sentinel->right = NULL;
			_sentinel->left = NULL;
			_sentinel->color = BLACK;
		}

		Node *	newNode (value_type const & val, Node * parent) {
			Node * tmp = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(tmp, Node());
			_alloc.construct(&tmp->data, val);
			tmp->parent = parent;
			tmp->right = _sentinel;
			tmp->left = _sentinel;
			tmp->color = RED;
			return tmp;
		}

		void clearHelper (Node *node) {
			if (node->left && node->left != _sentinel)
				clearHelper(node->left);
			if (node->right && node->right != _sentinel)
				clearHelper(node->right);
			if (node != _sentinel) {
				_alloc.destroy(&node->data);
				_nodeAlloc.destroy(node);
				_nodeAlloc.deallocate(node, 1);
			}
		}

		void	leftRotate (Node * x) {
			Node *	y;
			y = x->right;
			x->right = y->left;
			if (y->left != _sentinel)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _sentinel)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void	rightRotate (Node * x) {
			Node *	y;
			y = x->left;
			x->left = y->right;
			if (y->right != _sentinel)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _sentinel)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		Node *	insertNodeHelper (value_type const & val) {
			Node *	z = newNode(val, _sentinel);
			Node *	y = _sentinel;
			Node *	x = _root;
			while (x != _sentinel) {
				y = x;
				if (_comp(z->data, x->data))
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == _sentinel)
				_root = z;
			else if (_comp(z->data, y->data))
				y->left = z;
			else
				y->right = z;
			insertFixup(z);
			_size += 1;
			return z;
		}

		void	insertFixup (Node * z) {
			Node *	uncle;
			while (z->parent->color == RED) {
				if (z->parent == z->parent->parent->left) {
					uncle = z->parent->parent->right;
					if (uncle->color == RED) {
						z->parent->color = BLACK; //		 case 1
						uncle->color = BLACK; //			 case 1
						z->parent->parent->color = RED; //	 case 1
						z = z->parent->parent; //			 case 1
					}
					else {
						if (z == z->parent->right) {
							z = z->parent; //				 case 2
							leftRotate(z); //				 case 2
						}
						z->parent->color = BLACK; //		 case 3
						z->parent->parent->color = RED; //	 case 3
						rightRotate(z->parent->parent); //	 case 3
					}
				}
				else {
					uncle = z->parent->parent->left;
					if (uncle->color == RED) {
						z->parent->color = BLACK; //		 case 1
						uncle->color = BLACK; //			 case 1
						z->parent->parent->color = RED; //	 case 1
						z = z->parent->parent; //			 case 1
					}
					else {
						if (z == z->parent->left) {
							z = z->parent; //				 case 2
							rightRotate(z); //				 case 2
						}
						z->parent->color = BLACK; //		 case 3
						z->parent->parent->color = RED; //	 case 3
						leftRotate(z->parent->parent); //	 case 3
					}
				}
				if (z == _root)
					break;
			}
			_root->color = BLACK; //							 case 0
			ft::Node<value_type>::DG_tree(_root);
		}


	void	transplant(Node * a, Node * b) {
		if (a->parent == _sentinel)
			_root = b;
		else if (a == a->parent->left)
			a->parent->left = b;
		else
			a->parent->right = b;
		b->parent = a->parent;
	};
		
		void deleteNodeHelper (Node * z) {
			Node *	y = z;
			Node *	x;
			bool y_color = y->color;
			if (z->left == _sentinel) {
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _sentinel) {
				x = z->left;
				transplant(z, z->left);
			}
			else {
				y = minimum(z->right);
				y_color = y->color;
				x = y->right;
				if (y->parent != z) {
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			delete z;
			if (y_color == 0) {
				deleteFix(x);
			}
			_size -= 1;
			ft::Node<value_type>::DG_tree(_root);
		}

	void	deleteFix (Node * x) { // Called only when the deleted node was black.
		Node *	s; // s will be x's sibling
		while (x != _root && x != _sentinel && x->color == BLACK) {
			if (x == x->parent->left) { // if x is a left child
				s = x->parent->right;
				if (s->color == RED) { // CASE 1
					s->color = BLACK; // sibling is now back
					x->parent->color = RED; // parent is now red
					leftRotate(x->parent); // rotate parent
					s = x->parent->right; // assign s to x's new sibling (since x's position changed)
				}
				if (s->left->color == BLACK && s->right->color == BLACK) { // CASE 2
					s->color = RED; // sibling is now red
					x = x->parent; // move pointer to parent
				}
				else {
					if (s->right->color == BLACK) { // CASE 3 - this might be a _sentinel
						s->left->color = BLACK; // sibling's left child becomes black. This may be a _sentinel.
						s->color = RED; // sibling becomes red
						rightRotate(s);
						s = x->parent->right; // since we moved sibling, assign to s x's current sibling
					}
					// CASE 4
					s->color = x->parent->color; // sibling becomes the same color as its parent
					x->parent->color = BLACK; // x's parent becomes black
					s->right->color = BLACK; // sibling's child becomes black (may be _sentinel)
					leftRotate(x->parent);
					x = _root; // move x pointer to root, finishing the loop
				}
			}
			else { // same as above, but left and right are flipped
				s = x->parent->left;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == BLACK && s->right->color == 0) {
					s->color = RED;
					x = x->parent;
				}
				else {
					if (s->left->color == BLACK) {
						s->right->color = BLACK;
						s->color = RED;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					rightRotate(x->parent);
					x = _root;
				}
			}
		}
		x->color = BLACK;
	};
};

};
#endif
