#include <iostream>
#include <string>
#ifndef FT
# include <map>
# include <stack>
# include <vector>
# include <set>
namespace ft = std;
#else
# include "templates/map.hpp"
# include "templates/stack.hpp"
# include "templates/vector.hpp"
# include "templates/set.hpp"
#endif

#include <stdlib.h>

using namespace ft;

int	main (void) {
	vector<int>	vec; //default instanciation
	vec.assign(87, 42); // assign 2nd use
	vector<int> vec2(vec.begin(), vec.end()); // iterator instanciation
	vector<int> vec3(87, 42); // value instanciation
	vector<int> const cvec(vec); // const vector instanciation, by copy

	for (int i = 0; i < 5000; i++) {
		vec2.push_back(42); // push_back
		std::cout << "size: " << vec2.size() << ", capacity: " << vec2.capacity() << std::endl; //size and capacity check
	}
	vec2.pop_back(); //pop_back
	std::cout << "size: " << vec2.size() << ", capacity: " << vec2.capacity() << std::endl; //size and capacity check
	return 0;
}
