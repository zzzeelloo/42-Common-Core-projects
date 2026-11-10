/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:59:21 by anpetit           #+#    #+#             */
/*   Updated: 2024/11/27 16:29:07 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	const char	*last;

	last = NULL;
	i = 0;
	while (s[i])
	{
		if ((unsigned char)c == (unsigned char)s[i])
			last = &s[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return ((char *)last);
}

/*#include <stdio.h>

int main ()
{
   const char str[] = "Aerroretirgneor";

   const char ch = 'o';

   char *res;

   res = ft_strrchr(str, ch);

   printf("%s\n", res);

}*/
