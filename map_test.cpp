
#include <iostream>
#include <string>
#ifndef FT
# include <map>
# include <stack>
# include <map>
# include <set>
namespace ft = std;
#else
# include "templates/map.hpp"
#endif

#include <stdlib.h>

using namespace ft;

int	main (void) {
	map<int, int> m; //default instanciation
	int i = 1;
	while (i < 2147483647)
		pair<map<int, int>::iterator, bool> p;
		p = m.insert(make_pair((i / 4) * -3 + 256, i));
		std::cout << p.first->first << ", " << p.first->second << std::endl;
		i *= 2;
	}

	return 0;
}
