/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:12:02 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/24 13:00:44 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*st;

	i = 0;
	j = 0;
	len = ft_strltrim(s);
	if (s)
	{
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		if (!(st = (char *)malloc(sizeof(*st) * (len + 1))))
			return (NULL);
		while (j < len)
			st[j++] = s[i++];
		st[j] = '\0';
		return (st);
	}
	return (NULL);
}
