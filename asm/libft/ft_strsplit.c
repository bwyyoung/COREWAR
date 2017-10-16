/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:02:50 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/29 16:31:10 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *s, char c)
{
	int		j;
	int		k;
	char	**array;

	if (!s || !c)
		return (NULL);
	if (!(array = (char **)malloc(sizeof(char **) * (ft_strparts(s, c) + 1))))
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			k = 0;
			if (!(array[j] = ft_strnew(ft_strclen(s, c))))
				return (NULL);
			while (*s != c && *s)
				array[j][k++] = *s++;
			array[j++][k] = '\0';
		}
	}
	array[j] = 0;
	return (array);
}
