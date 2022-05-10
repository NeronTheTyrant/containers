#include <iostream>
#include <string>
#ifndef FT
# include <stack>
namespace ft = std;
#else
# include "../templates/stack.hpp"
#endif

#include <stdlib.h>

using namespace ft;

int	main(void) {
	stack<int> st; // default
	std::cout << st.empty() << std::endl; // empty
	for (int i = 0; i < 1000; i++) {
		st.push(i); // push
	}
	std::cout << st.size() << std::endl; // size
	std::cout << st.top() << std::endl; // top
	st.pop();
	std::cout << st.size() << std::endl;
}
