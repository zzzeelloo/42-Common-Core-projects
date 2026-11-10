/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:37:29 by zcherif           #+#    #+#             */
/*   Updated: 2026/04/10 22:37:31 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <exception>
# include <cstdlib>

template <typename T>
class Array {
	private:
		T*				_array;
		unsigned int	_size;

	public:
		Array(void);
		Array(unsigned int n);
		Array(Array const &src);
		~Array(void);

		Array &		operator=(Array const &rhs);
		T &			operator[](unsigned int index);
		T const &	operator[](unsigned int index) const;

		unsigned int	size(void) const;

		class OutOfBoundsException : public std::exception {
			public:
				virtual const char*	what() const throw();
		};
};

# include "Array.tpp"

#endif
