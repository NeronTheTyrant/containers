#ifndef NODE_HPP
# define NODE_HPP

namespace ft {

template<class T>
class Node {
	public:
	typedef T	value_type;

	value_type	data;
	Node *		parent;
	Node *		left;
	Node *		right;
	bool		color; // 0 == black, 1 == red

	Node() : parent(NULL), left(NULL), right(NULL) {};
	Node(Node const & src)
		: data(src.data), parent(src.parent), left(src.left), right(src.right), color(src.color) {};
	~Node() {};

	Node &	operator= (Node const & rhs) {
		parent = rhs.parent;
		left = rhs.left;
		right = rhs.right;
		data = rhs.data;
		color = rhs.color;
		return *this;
	}
};

};

#endif
