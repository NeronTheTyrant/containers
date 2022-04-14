// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/ft_algorithm.hpp"
#include "templates/vector.tpp"
#include <vector>
#include <map>
#include <list>
#include "templates/rbtree.hpp"
#include "templates/map.hpp"

using namespace ft;

int	main (void)
{
	map<int, int>	mymap;
	mymap.insert(make_pair(1, 15));
	mymap.insert(make_pair(1, 15));
	mymap.insert(make_pair(1, 15));
	mymap.insert(make_pair(1, 15));
	mymap.insert(make_pair(2, 15));
	mymap.insert(make_pair(3, 15));
	mymap.insert(make_pair(4, 15));
	mymap.insert(make_pair(1000000000, 15));
	mymap.insert(make_pair(87, 15));

	std::cout << "erase test" << std::endl;
	mymap.erase(4);
	map<int, int> map2(mymap);
	{
		map<int, int> map3 = map2;
		map3[8];
	}
	mymap.clear();
	map2[8];
	map2.key_comp();
	map2.value_comp();
	map<int, int>::iterator it = map2.begin();
	for (map<int, int>::iterator ite = map2.end(); it != ite; it++) {
		std::cout << it->first << std::endl;
	}
	std::cout << map2.size() << ", " << map2.empty() << ", " << map2.max_size() << std::endl;
	map2[8];
	std::list<pair<const int, int> > li(map2.begin(), map2.end());
	std::list<pair<const int, int> >::iterator lit = li.begin();
	std::list<pair<const int, int> >::iterator lite = li.end();
	for (; lit != lite; lit++)
		std::cout << lit->first << std::endl;
	map2.clear();
	map2.insert(li.begin(), li.end());
	it = map2.begin();
	for (map<int, int>::iterator ite = map2.end(); it != ite; it++) {
		std::cout << it->first << std::endl;
	}
}
