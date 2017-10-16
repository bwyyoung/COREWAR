/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:57:32 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/22 09:23:14 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(little);
	if (j == 0)
		return ((char *)big);
	while (big[i])
	{
		if (big[i] == little[0])
			if (ft_strncmp((char *)big + i, (char *)little, j) == 0)
				return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
