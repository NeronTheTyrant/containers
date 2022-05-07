#ifndef RBTREE_HPP
# define RBTREE_HPP
#include "tree_iterator.hpp"
#include "node.hpp"

#define BLACK	0
#define RED		1

namespace ft {

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
			while (node->left != _sentinel && node->left)
				node = node->left;
			return node;
		}

		Node *	maximum(Node * node) const {
			while (node->right != _sentinel && node->right)
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

		void deleteNode(const_iterator it) {
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
			setNodeColor(_sentinel, BLACK);
		}

		Node *	newNode (value_type const & val, Node * parent) {
			Node * tmp = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(tmp, Node());
			_alloc.construct(&tmp->data, val);
			tmp->parent = parent;
			tmp->right = _sentinel;
			tmp->left = _sentinel;
			setNodeColor(tmp, RED);
			return tmp;
		}

		void clearHelper (Node *node) {
			if (node->left && node->left != _sentinel)
				clearHelper(node->left);
			if (node->right && node->right != _sentinel)
				clearHelper(node->right);
			if (node != _sentinel) {
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
			while (getNodeColor(z->parent) == RED) {
				if (z->parent == z->parent->parent->left) {
					uncle = z->parent->parent->right;
					if (getNodeColor(uncle) == RED) {
						setNodeColor(z->parent, BLACK); //		 case 1
						setNodeColor(uncle, BLACK); //			 case 1
						setNodeColor(z->parent->parent, RED); //	 case 1
						z = z->parent->parent; //			 case 1
					}
					else {
						if (z == z->parent->right) {
							z = z->parent; //				 case 2
							leftRotate(z); //				 case 2
						}
						setNodeColor(z->parent, BLACK); //		 case 3
						setNodeColor(z->parent->parent, RED); //	 case 3
						rightRotate(z->parent->parent); //	 case 3
					}
				}
				else {
					uncle = z->parent->parent->left;
					if (getNodeColor(uncle) == RED) {
						setNodeColor(z->parent, BLACK); //		 case 1
						setNodeColor(uncle, BLACK); //			 case 1
						setNodeColor(z->parent->parent, RED); //	 case 1
						z = z->parent->parent; //			 case 1
					}
					else {
						if (z == z->parent->left) {
							z = z->parent; //				 case 2
							rightRotate(z); //				 case 2
						}
						setNodeColor(z->parent, BLACK); //		 case 3
						setNodeColor(z->parent->parent, RED); //	 case 3
						leftRotate(z->parent->parent); //	 case 3
					}
				}
				if (z == _root)
					break;
			}
			setNodeColor(_root, BLACK); //							 case 0
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
			Node *parent = z->parent;
			bool y_color = getNodeColor(y);
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
				parent = y->parent;
				y_color = getNodeColor(y);
				x = y->right;
				if (y->parent != z) {
					parent = y->parent;
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				else
					parent = y;
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				setNodeColor(y, getNodeColor(z));
			}
			_nodeAlloc.destroy(z);
			_nodeAlloc.deallocate(z, 1);
			if (y_color == BLACK) {
				deleteFix(x, parent);
			}
			_size -= 1;
		}

	void	deleteFix (Node * x, Node *parent) { // Called only when the deleted node was black.
		Node * s; // x's sibling
		while (x != _root && getNodeColor(x) == BLACK) {
			if (x != _sentinel && x != NULL)
				parent = x->parent;
			if (x == parent->left) { // if x is a left child
				s = parent->right;
				if (getNodeColor(s) == RED) { // CASE 1
					setNodeColor(s, BLACK); // sibling is now back
					setNodeColor(parent, RED); // parent is now red
					leftRotate(parent); // rotate parent
					s = parent->right; // assign s to x's new sibling (since x's position changed)
				}
				if (!s || (getNodeColor(s->left) == BLACK && getNodeColor(s->right) == BLACK)) { // CASE 2
					setNodeColor(s, RED); // sibling is now red
					x = parent;
				}
				else {
					if (getNodeColor(s->right) == BLACK) { // CASE 3 - this might be a _sentinel
						setNodeColor(s->left, BLACK); // sibling's left child becomes black. This may be a _sentinel.
						setNodeColor(s, RED); // sibling becomes red
						rightRotate(s);
						s = parent->right; // since we moved sibling, assign to s x's current sibling
					}
					// CASE 4
					setNodeColor(s, getNodeColor(parent)); // sibling becomes the same color as its parent
					setNodeColor(parent, BLACK); // x's parent becomes black
					setNodeColor(s->right, BLACK); // sibling's child becomes black (may be _sentinel)
					leftRotate(parent);
					x = _root; // move x pointer to root, finishing the loop
				}
			}
			else { // same as above, but left and right are flipped
				s = parent->left;
				if (getNodeColor(s) == RED) {
					setNodeColor(s, BLACK);
					setNodeColor(parent, RED);
					rightRotate(parent);
					s = parent->left;
				}

				if (!s || (getNodeColor(s->right) == BLACK && getNodeColor(s->left) == BLACK)) {
					setNodeColor(s, RED);
					x = parent;
				}
				else {
					if (getNodeColor(s->left) == BLACK) {
						setNodeColor(s->right, BLACK);
						setNodeColor(s, RED);
						leftRotate(s);
						s = parent->left;
					}

					setNodeColor(s, getNodeColor(parent));
					setNodeColor(parent, BLACK);
					setNodeColor(s->left, BLACK);
					rightRotate(parent);
					x = _root;
				}
			}
			if (x == _sentinel)
				break;
		}
		setNodeColor(x, BLACK);
	};

	void	setNodeColor (Node *node, bool color) {
		if (node != NULL && node != _sentinel)
			node->color = color;
	}

	bool	getNodeColor (Node *node) {
		if (node == NULL || node == _sentinel)
			return BLACK;
		return node->color;
	}

};

};
#endif
