/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:19:30 by zcherif           #+#    #+#             */
/*   Updated: 2023/09/28 12:31:17 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

/*int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	printf("ft_isalpha:%d \n", ft_isalpha(atoi(argv[1])));
	printf("ft_isalpha:%d \n", isalpha(atoi(argv[1])));
	return(0);
}*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * DESCRIPCION: la funcion comprueba que el caracter que recibe, sea un
 * char empleando un int como parametro de entrada.
 * INPUT: integuer c
 * MAKE: comprueba que esta dentro del rango de chars alfabeticos
 * OUTPUT: si es un char alfabetico retorna 1 y si no, retorna 0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
