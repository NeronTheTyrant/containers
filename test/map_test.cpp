
#include <iostream>
#include <string>
#ifndef FT
# include <map>
namespace ft = std;
#else
# include "../templates/map.hpp"
#endif

#include <stdlib.h>

using namespace ft;

int	main (void) {
	map<int, int> m; //default instanciation
	int i = 1;
	while (i < 30) {
		map<int, int>::iterator it;
		it = m.insert(make_pair((1 << i) * (i % 2 ? -1 : 1), 1 << i)).first; // insert (1)
		i++;
	}
	map<int, int>::iterator it = m.begin();
	for (map<int, int>::iterator ite = m.end(); it != ite; it++) {
		std::cout << it->first << ", " << it->second << std::endl;
	}
	map<int, int> m2(m); // instanciation by copy
	if (m == m2)
		std::cout << "they're the same!" << std::endl;
	map<int, int> m3(m2.begin(), m2.end()); // instanciation by iterator
	if (m2 == m3)
		std::cout << "they're the same!" << std::endl;
	m2.insert(m2.begin(), make_pair(490, 82)); // insert (2)
	if (m2 == m3)
		std::cout << "something's wrong" << std::endl;
	m2 = m3;
	if (m2 == m3)
		std::cout << "they're the same!" << std::endl;
	it = m3.find(-256); // find
	if (it != m3.end())
		std::cout << m3.find(-256)->second << std::endl;
	else
		std::cout << "could not find key -256" << std::endl;
	m3[-256] = 78; // access
	std::cout << m3.find(-256)->second << std::endl;
	m2.insert(m3.begin(), m3.end()); // insert (3)
	if (m2 != m3)
		std::cout << "something's wrong" << std::endl;
	m.insert(m2.begin(), m2.end());
	m2.erase(++(++(++(m2.begin())))); // erase (1)
	m3.erase(-8388608); // erase (2)
	m.erase(++(++(++(m.begin()))), ++(++(++(++(m.begin()))))); // erase (3)
	if (m != m2)
		std::cout << "m != m2" << std::endl;
	if (m2 != m3)
		std::cout << "m2 != m3" << std::endl;
	if (m3 != m)
		std::cout << "m3 != m" << std::endl;
	m.clear(); // clear
	m.swap(m3); // swap
	if (m != m2)
		std::cout << "m != m2" << std::endl;
	std::cout << "m3.empty(): " << m3.empty() << std::endl;
	map<int, int>::key_compare kc = m3.key_comp(); // key_comp
	(void)kc;
	map<int, int>::value_compare vc = m3.value_comp(); // value_comp
	(void)vc;
	std::cout << m2.count(256) << m2.count(215864) << m2.count(-1) << std::endl; // count
	std::cout << m2.lower_bound(-8)->second << " " << m2.upper_bound(-8)->second << std::endl;
	pair<map<int, int>::iterator, map<int, int>::iterator > p = m2.equal_range(-8);
	std::cout << "<" << p.first->first << ", " << p.first->second << "> <";
	std::cout << p.second->first << ", " << p.second->second << ">" << std::endl;
	m2.get_allocator();
	return 0;
}
