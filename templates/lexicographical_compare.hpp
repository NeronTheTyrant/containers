/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:01:00 by mlebard           #+#    #+#             */
/*   Updated: 2022/03/28 18:01:37 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2) {
	while (first1 != last1) {
		if (first2 == last2)
			return false;
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
		first1++;
		first2++;
	}
	return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2,
							Compare comp) {
	while (first1 != last1) {
		if (first2 == last2)
			return false;
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2, *first1))
			return false;
		first1++;
		first2++;
	}
	return (first2 != last2);
}

};

#endif
