/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:26:44 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:26:49 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		print_widthpad(int width, int strlen, char c, t_ap *arg)
{
	while (strlen < width)
	{
		ft_putchar_fd(c, arg->fd);
		strlen++;
	}
}

size_t		ft_nlen_prefix(uintmax_t u, char *base, t_ap *arg, char *prefix)
{
	size_t	nlen;
	size_t	len;

	nlen = ft_calc_nlen(u, base);
	if (u == 0 && arg->precisionflag && arg->precision == 0)
		len = 0;
	else
		len = arg->precisionflag ? ft_max(nlen, arg->precision) : nlen;
	if (arg->forcesign && prefix != NULL && u != 0)
		len += ft_strlen(prefix);
	return (len);
}

size_t		ft_calc_nlen(uintmax_t n, char *base)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(base);
	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= len;
		i++;
	}
	return (i);
}
