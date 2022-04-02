#ifndef MAP_HPP
# define MAP_HPP

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

};

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
};

}
