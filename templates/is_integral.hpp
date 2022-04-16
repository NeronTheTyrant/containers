/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:52:37 by mlebard           #+#    #+#             */
/*   Updated: 2022/04/15 17:31:25 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft {

template <typename>
struct is_integral_base						{ static bool const value = false;};

template <>
struct is_integral_base<bool>				{ static bool const value = true;};

template <>
struct is_integral_base<char>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned char>		{ static bool const value = true;};
/*
template <>
struct is_integral_base<char16_t>			{ static bool const value = true;};

template <>
struct is_integral_base<char32_t>			{ static bool const value = true;};
*/
template <>
struct is_integral_base<wchar_t>			{ static bool const value = true;};

template <>
struct is_integral_base<short>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned short>		{ static bool const value = true;};

template <>
struct is_integral_base<int>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned int>		{ static bool const value = true;};

template <>
struct is_integral_base<long>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned long>		{ static bool const value = true;};

template <>
struct is_integral_base<long long>			{ static bool const value = true;};

template <>
struct is_integral_base<unsigned long long>	{ static bool const value = true;};

template <class T>
struct is_integral : is_integral_base<T> {};

};

#endif
