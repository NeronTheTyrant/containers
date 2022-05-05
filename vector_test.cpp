#include <iostream>
#include <string>
#ifndef FT
# include <map>
# include <stack>
# include <vector>
# include <set>
namespace ft = std;
#else
# include "templates/vector.hpp"
#endif

#include <stdlib.h>

using namespace ft;

int	main (void) {
	vector<int> vec; //default instanciation
	vec.assign(87, 42); // assign (2)
	vector<int> vec2(vec.begin(), vec.end()); // iterator instanciation
	vector<int> vec3(87, 42); // value instanciation
	vector<int> vec4;
	vec4.assign(vec3.begin(), vec3.end()); // assign (1)
	vector<int> const cvec(vec); // const vector instanciation, by copy
	
	std::cout << "size: " << vec.size() << std::endl; // size
	std::cout << "max size: " << vec.max_size() << std::endl; // max_size
	std::cout << "capacity: " << vec.capacity() << std::endl; // capacity
	std::cout << "empty: " << vec.empty() << std::endl; // empty
	vec.resize(32); // resize smaller
	std::cout << "new size: " << vec.size() << std::endl;
	vec.resize(95); // resize bigger
	std::cout << "new size: " << vec.size() << std::endl;
	std::cout << "new capacity: " << vec.capacity() << std::endl;
	vec.reserve(50000); // reserve
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << vec[42] << " " << cvec[42] << std::endl; // [] operator
	std::cout << vec.at(42) << " " << cvec.at(42) << std::endl; // at
	std::cout << vec.front() << " " << cvec.front() << std::endl; // front
	std::cout << vec.back() << " " << cvec.back() << std::endl;

	for (int i = 0; i < 5000; i++) {
		vec2.push_back(42); // push_back
		std::cout << "size: " << vec2.size() << ", capacity: " << vec2.capacity() << std::endl; //size and capacity check
	}
	vec2.pop_back(); //pop_back
	std::cout << "size: " << vec2.size() << ", capacity: " << vec2.capacity() << std::endl; //size and capacity check
	vec3.insert(vec3.begin(), vec2.begin(), vec2.end() - 1000); // insert (3)
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl; //size and capacity check
	vec3.insert(vec3.end(), *vec2.rbegin()); // insert (1)
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl; //size and capacity check
	vec3.insert(vec3.end(), 8520, 69); // insert(2)
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl; //size and capacity check
	std::cout << vec3.back() << std::endl;
	vec3.erase(--vec3.end()); // erase (1)
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl; //size and capacity check
	vec3.erase(vec3.begin(), vec3.end());
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl; //size and capacity check
	vec3.swap(vec4);
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl; //size and capacity check
	std::cout << "size: " << vec4.size() << ", capacity: " << vec4.capacity() << std::endl; //size and capacity check
	vec4.clear();
	vec.get_allocator();
	return 0;
}
