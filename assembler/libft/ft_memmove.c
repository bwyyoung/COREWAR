/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:23:36 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/21 14:55:49 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*str1;
	char			*str2;

	i = 0;
	str1 = (char *)dst;
	str2 = (char *)src;
	if (str2 < str1)
	{
		len--;
		while ((int)len >= 0)
		{
			str1[len] = str2[len];
			len--;
		}
	}
	else
		ft_memcpy(str1, str2, len);
	return (dst);
}
