// enable_if example: two ways of using enable_if
#include <iostream>
#include "templates/enable_if.hpp"
#include "templates/is_integral.hpp"

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename enable_if<is_integral<T>::value,bool>::type
is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
		 class = typename enable_if<is_integral<T>::value>::type>
		 bool is_even (T i) {return !bool(i%2);}

		 int main() {

			 std::string i = "hello";    // code does not compile if type of i is not integral

			 std::cout << std::boolalpha;
			 std::cout << "i is odd: " << is_odd(i) << std::endl;
			 std::cout << "i is even: " << is_even(i) << std::endl;

			 return 0;
		 }
