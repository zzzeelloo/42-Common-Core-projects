/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:49:11 by zcherif           #+#    #+#             */
/*   Updated: 2025/11/01 12:52:08 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) {

	std::cout << W << "Animal" << G << " created !" << RES << std::endl;
}

Animal::Animal(const Animal &copy) {

	_type = copy._type;
	std::cout << W << "Animal" << G << " created !" << RES << std::endl;
}

Animal	&Animal::operator=(const Animal &copy) {

	_type = copy._type;
	std::cout << W << "Animal" << G << " created !" << RES << std::endl;
	return (*this);
}

Animal::~Animal() {

	std::cout << W << "Animal " << R << " destroyed" << RES << std::endl;
}

void	Animal::makeSound() {

	std::cout << Y << "* Silence *" << RES << std::endl;
}

