#ifndef MAP_HPP
# define MAP_HPP

namespace ft {

template <class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> >
class map {

	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::difference_type			difference_type;
		typedef typename Alloc::size_type				size_type;
	
	template <class Key, class T, class Compare, class Alloc>
		class map<Key, T, Compare, Alloc>::value_compare {
				friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {};
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (value_type const & x, value_type const & y) const {
					return comp(x.first, y.first);
				}
		};
	protected:
		RBT<value_type, value_compare>	rbtree;
	public:
		

};

#endif
