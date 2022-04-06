// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/ft_algorithm.hpp"
#include "templates/vector.tpp"
#include <vector>
#include <map>
#include "templates/rbtree.hpp"
int	main (void)
{
	ft::RBT<ft::pair<int, int> >	rbt;
	rbt.insertNode(ft::make_pair(15, 32));
	rbt.insertNode(ft::make_pair(13, 58));
	rbt.insertNode(ft::make_pair(8, 78));
	rbt.insertNode(ft::make_pair(58, 32));
	rbt.insertNode(ft::make_pair(2, 58));
	rbt.insertNode(ft::make_pair(100, 78));

	rbt.deleteNode(ft::make_pair(13, 58));

}
