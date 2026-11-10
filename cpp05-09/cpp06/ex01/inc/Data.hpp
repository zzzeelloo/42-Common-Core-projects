/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:51:42 by zcherif           #+#    #+#             */
/*   Updated: 2026/04/10 22:00:00 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
	std::string stringValue;
	int intValue;

	Data();
	Data(const Data &src);
	Data &operator=(const Data &rhs);
	~Data();
};

#endif
