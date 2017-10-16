/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 12:51:55 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/22 13:46:31 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(little);
	if (j == 0)
		return ((char *)big);
	while (big[i] && (int)i <= ((int)len - (int)j))
	{
		if (big[i] == little[0])
			if (ft_strncmp((char *)big + i, (char *)little, j) == 0)
				return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
