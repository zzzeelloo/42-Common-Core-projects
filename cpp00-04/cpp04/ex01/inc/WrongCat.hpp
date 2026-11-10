/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:03:01 by zcherif           #+#    #+#             */
/*   Updated: 2025/11/01 13:03:05 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class   WrongCat: public WrongAnimal {

    public:
        WrongCat(void);
        WrongCat(const WrongCat &copy);
        WrongCat    &operator=(const WrongCat &copy);
        ~WrongCat(void);

        void    makeSound(void);
};

#endif