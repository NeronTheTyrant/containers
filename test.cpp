#include <list>
#include "ft_algorithm.hpp"
#include "map.hpp"
#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	ft::map<T1, T2> mp(lst.begin(), lst.end());

	mp.erase(++mp.begin());

	mp.erase(mp.begin());
	mp.erase(--mp.end());

	mp.erase(mp.begin(), ++(++(++mp.begin())));
	mp.erase(--(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
	mp.erase(--(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	mp.erase(mp.begin(), mp.end());

	return (0);
}
