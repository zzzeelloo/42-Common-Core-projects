/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:49:39 by zcherif           #+#    #+#             */
/*   Updated: 2025/10/23 11:52:40 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char **argv) {

	Harl	harl;
	
	if (argc != 1) {
		std::cout << "No arguments required !" << std::endl;
		return (1);
	}
	(void)argv;
	
	std::cout << GREEN << "[DEBUG]:" << RESET << std::endl;
	harl.complain("DEBUG");
	std::cout << CYAN << "[INFO]:" RESET << std::endl;
	harl.complain("INFO");
	std::cout << YELLOW << "[WARNING]:" << RESET << std::endl;
	harl.complain("WARNING");
	std::cout << RED << "[ERROR]:" << RESET << std::endl;
	harl.complain("ERROR");

	return (0);
}
