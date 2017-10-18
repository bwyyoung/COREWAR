/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:41:36 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/18 17:43:46 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;
	char	*temp;

	str = ft_strnew(len);
	if (!str)
		return (NULL);
	temp = str;
	while (len--)
		*temp++ = *src++;
	return (str);
}
