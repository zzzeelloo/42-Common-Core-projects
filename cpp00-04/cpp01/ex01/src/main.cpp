/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:14:42 by zcherif           #+#    #+#             */
/*   Updated: 2025/10/19 20:19:46 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(int argc, char **argv) {

	int		zombies;
	Zombie	*horde;

	if (argc != 1) {
		std::cout << "No argumentz needed... brainzzz" << std::endl;
		return (1);
	}
	(void)argv;
	zombies = 5;
	horde = zombieHorde(zombies, "Zombie ghoul");
	if (!horde) {
		return (1);
	}
	for (int i = 0; i < zombies; i++) {
		std::cout << i << " "; horde[i].announce();
	};
	delete [] horde;
	return (0);
}
