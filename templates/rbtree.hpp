#ifndef RBTREE_HPP
# define RBTREE_HPP

namespace ft {


template <T>
class Node {
	public:
		typedef T	value_type;

		value_type	data;
		Node *		parent;
		Node *		left;
		Node *		right;
		bool		color; // 0 is black, 1 is red

		Node() : parent(NULL), left(NULL), right(NULL) {};
		Node(Node const & src) : parent(src.parent), left(src.left), right(right.left), color(src.color) {};
		~Node() {};

		Node &	operator= (Node const & rhs) {
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			color = rhs.color;
			return *this;
		};
};

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class RBT {
	protected:
		#define BLACK	0
		#define RED		1
		Node *				root;
		Node *				sentinel; // leaf
		allocator_type		alloc;
		node_allocator_type	nodeAlloc;
		key_compare			comp;

	public:
		typedef T						value_type;
		typedef Compare					key_compare;
		typedef Node<value_type>		Node;
		typedef Alloc					allocator_type;
		typedef std::allocator<Node>	node_allocator_type;

		RBT(allocator_type const & allocator = allocator_type())
			: root(NULL), sentinel(NULL), alloc(allocator), nodeAlloc(node_allocator_type()) {
			initSentinel();
			root = sentinel;
		};

		void	initSentinel() {
			sentinel = nodeAlloc.allocate(1);
			nodeAlloc.construct(sentinel, node());
			alloc.construct(&sentinel->data, value_type());
			sentinel->parent = NULL;
			sentinel->right = NULL;
			sentinel->left = NULL;
			sentinel->color = BLACK;
		};

		Node *	newNode (value_type const & val, Node * parent) {
			Node * tmp = nodeAlloc.allocate(1);
			nodeAlloc.construct(tmp, node());
			alloc.construct(&tmp->data, val);
			tmp->parent = parent;
			tmp->right = sentinel;
			tmp->left = sentinel;
			tmp->color = RED;
		};
		
		void	leftRotate (Node * x) {
			Node *	y;
			y = x->right;
			x->right = y->left;
			if (y->left != sentinel)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == sentinel)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		};

		void	rightRotate (Node * x) {
			Node *	y;
			y = x->left;
			x->left = y->right;
			if (y->right != sentinel)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == sentinel)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		};

		void	insertNode(value_type const & val) {
			Node *	z = newNode(val, sentinel);
			Node *	y = nullptr;
			Node *	x = root;
			while (x != sentinel) {
				y = x;
				if (comp(z->data, x->data)
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == nullptr)
				root = z;
			else if (comp(z->data, y->data))
				y->left = z;
			else
				y->right = z;
			insertFixup(z);
		};

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
				if (z == root)
					break;
			}
			root->color = BLACK //							 case 0
		};

	void deleteNode(int key) {
		Node * z = sentinel;
		Node * tmp = root;
		while (tmp != sentinel) {
			if (tmp->data == key) {
				z = tmp;
			}

			if (tmp->data <= key) {
				tmp = tmp->right;
			}
			else {
				tmp = tmp->left;
			}
		}
		if (z == sentinel) {
			cout << "Key not found in the tree" << endl;
			return;
		}
		Node *	y = z;
		Node *	x;
		bool y_color = y->color;
		if (z->left == sentinel) {
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == sentinel) {
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
	};

	void	transplant(Node * a, Node * b) {
		if (a->parent == sentinel)
			root = b;
		else if (a == a->parent->left)
			a->parent->left = b;
		else
			a->parent->right = b;
		b->parent = a->parent;
	};

	void	deleteFix (Node * x) { // Called only when the deleted node was black.
		Node *	s; // s will be x's sibling
		while (x != root && x->color == BLACK) {
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
					if (s->right->color = BLACK) { // CASE 3 - this might be a sentinel
						s->left->color = BLACK; // sibling's left child becomes black. This may be a sentinel.
						s->color = RED; // sibling becomes red
						rightRotate(s);
						s = x->parent->right; // since we moved sibling, assign to s x's current sibling
					}
					// CASE 4
					s->color = x->parent->color; // sibling becomes the same color as its parent
					x->parent->color = BLACK; // x's parent becomes black
					s->right->color = BLACK; // sibling's child becomes black (may be sentinel)
					leftRotate(x->parent);
					x = root; // move x pointer to root, finishing the loop
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
					x = root;
				}
			}
		}
		x->color = BLACK; 
	};
};

};
#endif