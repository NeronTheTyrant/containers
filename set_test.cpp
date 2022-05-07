
#include <iostream>
#include <string>
#ifndef FT
# include <set>
# include <stack>
# include <set>
# include <set>
namespace ft = std;
#else
# include "templates/set.hpp"
#endif

#include <stdlib.h>

using namespace ft;

int	main (void) {
	set<int> s; //default instanciation
	int i = 1;
	while (i < 30) {
		set<int>::iterator it;
		it = s.insert((1 << i) * (i % 2 ? -1 : 1)).first; // insert (1)
		i++;
	}
	set<int>::iterator it = s.begin();
	for (set<int>::iterator ite = s.end(); it != ite; it++) {
		std::cout << *it << ", " << *it << std::endl;
	}
	set<int> s2(s); // instanciation by copy
	if (s == s2)
		std::cout << "they're the same!" << std::endl;
	set<int> s3(s2.begin(), s2.end()); // instanciation by iterator
	if (s2 == s3)
		std::cout << "they're the same!" << std::endl;
	s2.insert(s2.begin(), 82); // insert (2)
	if (s2 == s3)
		std::cout << "something's wrong" << std::endl;
	s2 = s3;
	if (s2 == s3)
		std::cout << "they're the same!" << std::endl;
	it = s3.find(-256); // find
	if (it != s3.end())
		std::cout << *s3.find(-256) << std::endl;
	else
		std::cout << "could not find key -256" << std::endl;
	s2.insert(s3.begin(), s3.end()); // insert (3)
	if (s2 != s3)
		std::cout << "something's wrong" << std::endl;
	s.insert(s2.begin(), s2.end());
	s2.erase(++(++(++(s2.begin())))); // erase (1)
	s3.erase(-8388608); // erase (2)
	s.erase(++(++(++(s.begin()))), ++(++(++(++(s.begin()))))); // erase (3)
	if (s != s2)
		std::cout << "s != s2" << std::endl;
	if (s2 != s3)
		std::cout << "s2 != s3" << std::endl;
	if (s3 != s)
		std::cout << "s3 != s" << std::endl;
	s.clear(); // clear
	s.swap(s3); // swap
	if (s != s2)
		std::cout << "s != s2" << std::endl;
	std::cout << "s3.empty(): " << s3.empty() << std::endl;
	set<int>::key_compare kc = s3.key_comp(); // key_comp
	set<int>::value_compare vc = s3.value_comp(); // value_comp
	std::cout << s2.count(256) << s2.count(215864) << s2.count(-1) << std::endl; // count
	std::cout << *s2.lower_bound(-8) << " " << *s2.upper_bound(-8) << std::endl;
	pair<set<int>::iterator, set<int>::iterator > p = s2.equal_range(-8);
	std::cout << "<" << *p.first << "> <";
	std::cout << *p.second << ">" << std::endl;
	s2.get_allocator();
	return 0;
}
