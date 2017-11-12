/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:26:09 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/19 15:54:33 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char		*ft_concat(char *s1, char *s2)
{
	char	*new;

	new = NULL;
	if (s1 && s2)
	{
		if (!(new = (char *)malloc(sizeof(char) * ft_strlen(s1) +
		ft_strlen(s2) + 1)))
			return (NULL);
		ft_strcpy(new, s1);
		ft_strcat(new, s2);
		free(s1);
	}
	return (new);
}

void		reverse_bytes(char *str, int start, int n)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = n - 1;
	while (i < n / 2)
	{
		tmp = str[start + i];
		str[start + i] = str[start + j];
		str[start + j] = tmp;
		i++;
		j--;
	}
}
