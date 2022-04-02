// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/ft_algorithm.hpp"
#include "templates/vector.tpp"
#include <vector>
#include <map>
int	main (void)
{
	std::map<int, int>	map;
	map.insert(std::make_pair(1, 1));
	map.insert(std::make_pair(2,2));
	map.insert(std::make_pair(3,3));
	std::map<int, int>::iterator ite = map.end();
	std::cout << "first: " << ite->first << " second: " << ite->second << std::endl;
	--ite;
	std::cout << "first: " << ite->first << " second: " << ite->second << std::endl;
}
