// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/ft_algorithm.hpp"
#include "templates/vector.tpp"
#include <vector>
#include <map>
#include "templates/rbtree.hpp"
int	main (void)
{
	ft::RBT<int>	rbt;
	rbt.insertNode(15);
	rbt.insertNode(13);
	rbt.insertNode(8);
	ft::Node<int>::DG_tree(rbt.root);
}
