/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 17:57:08 by byoung-w          #+#    #+#             */
/*   Updated: 2014/09/03 17:57:22 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isint(char const *p)
{
	int		i;
	char	*str;

	if (!p || (p[0] == '\0'))
		return (0);
	i = ft_atoi(p);
	str = ft_itoa(i);
	if (!ft_strcmp(p, str))
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (0);
}
