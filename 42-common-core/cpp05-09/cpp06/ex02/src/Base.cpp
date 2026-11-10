/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:53:39 by zcherif           #+#    #+#             */
/*   Updated: 2026/04/10 22:00:00 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::Base() {}

Base::Base(const Base &src) { *this = src; }

Base &Base::operator=(const Base &rhs) { (void)rhs; return (*this); }

Base::~Base() {}
