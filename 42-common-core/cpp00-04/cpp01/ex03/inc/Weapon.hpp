/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:52:37 by zcherif           #+#    #+#             */
/*   Updated: 2025/10/22 19:39:30 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon {

	private:
		std::string _type;
	public:
		Weapon(void);
		Weapon(std::string type);
		~Weapon(void);
		
		const std::string&	getType(void) const;
		void				setType(std::string type);
};

#endif
