template <class T1, class T2>
struct pair {
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair () {}; // default
	template <class U, class V>
		pair (pair<U, V> const & pr) : first(pr.first), second(pr.second) {}; // copy
		pair (first_type const & a, second_type const & b) : first(a), second(b) {}; //assign

		~pair () {};

		pair & operator= (pair const & pr) {
			first = pr.first;
			second = pr.second;
			return *this;
		};
};

template <class T1, class T2>
bool operator== (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!= (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator< (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator< (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<= (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator> (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>= (pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
	return !(lhs < rhs);
}
