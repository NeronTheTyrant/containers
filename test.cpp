// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/ft_algorithm.hpp"
#include "templates/vector.tpp"
#include <vector>

int	main (void)
{
	ft::vector<int> v;
	std::cout << v.size() << ", " << v.capacity() << std::endl;
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		std::cout << "size: " << v.size() << ", " << "cap: " << v.capacity() << std::endl;
	}
	ft::vector<int> ve;
	if (ve.begin() == ve.end())
	{
		std::cout << "they're equal" << std::endl;
	}
	std::cout << v.back() << std::endl;
	std::cout << v.front() << std::endl;
	ft::vector<int> vect(150, 100);
	ft::vector<int> vector(v.begin(), v.end());
	ft::vector<int>::iterator it;
	for (it = vect.begin(); it != vect.end(); it++)
		std::cout << *it << ", " << std::endl;
	std::cout << "BREAK BREAK" << std::endl;
	for (it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << ", " << std::endl;
}
