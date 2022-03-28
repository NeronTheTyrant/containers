// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/ft_algorithm.hpp"
#include "templates/vector.tpp"

int	main (void)
{
	ft::vector<int> v;
	std::cout << v.size() << ", " << v.capacity() << std::endl;
}
