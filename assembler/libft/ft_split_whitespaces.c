/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 12:33:40 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/29 16:30:21 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
			i++;
		count++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			i++;
	}
	return (count);
}

static int		ft_wd_ln(char *str)
{
	int ln;

	ln = 0;
	while (*str != ' ' && *str != '\t' && *str != '\n' && *str)
	{
		ln++;
		str++;
	}
	return (ln);
}

char			**ft_split_whitespaces(char *str)
{
	int		j;
	int		k;
	char	**array;

	if (!str)
		return (NULL);
	if (!(array = (char **)malloc(sizeof(char **) * (ft_word_count(str) + 1))))
		return (NULL);
	j = 0;
	while (*str)
	{
		while ((*str == ' ' || *str == '\t' || *str == '\n') && *str)
			str++;
		if (*str)
		{
			k = 0;
			if (!(array[j] = ft_strnew(ft_wd_ln(str))))
				return (NULL);
			while (*str != ' ' && *str != '\t' && *str != '\n' && *str)
				array[j][k++] = *str++;
			array[j++][k] = '\0';
		}
	}
	array[j] = 0;
	return (array);
}
