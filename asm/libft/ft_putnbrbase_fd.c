/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:22:16 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/14 15:23:32 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrbase_fd_new(uintmax_t nbr, char *base, size_t baselen,
		int fd)
{
	if (nbr >= baselen)
	{
		ft_putnbrbase_fd_new(nbr / baselen, base, baselen, fd);
		ft_putnbrbase_fd_new(nbr % baselen, base, baselen, fd);
	}
	else
		ft_putchar_fd(base[nbr], fd);
}

void		ft_putnbrbase_fd(uintmax_t nbr, char *base, int fd)
{
	ft_putnbrbase_fd_new(nbr, base, ft_strlen(base), fd);
}
