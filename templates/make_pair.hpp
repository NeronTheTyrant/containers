/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:02:00 by mlebard           #+#    #+#             */
/*   Updated: 2022/03/28 18:05:08 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
# define MAKE_PAIR_HPP

#include "pair.hpp"

namespace ft {

template <class T1, class T2>
pair<T1, T2>	make_pair (T1 x, T2 y) {
	return pair<T1, T2>(x, y);
}

};

#endif
