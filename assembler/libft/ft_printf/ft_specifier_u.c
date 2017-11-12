/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:25:15 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:25:17 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int			ft_uint(uintmax_t u, t_ap *arg, char *base, char *prefix)
{
	size_t			nlen;
	size_t			len;

	if (arg->precisionflag)
		arg->padzero = 0;
	nlen = ft_calc_nlen(u, base);
	if (arg->widthflag && !arg->leftpos && arg->padzero)
	{
		arg->precision = arg->precisionflag ? ft_max(arg->width,
				arg->precision) : ft_max(arg->width, nlen);
		arg->precisionflag = 1;
		arg->widthflag = 0;
	}
	len = ft_nlen_prefix(u, base, arg, prefix);
	if (arg->widthflag && !arg->leftpos)
		print_widthpad(arg->width, len, ' ', arg);
	if (arg->forcesign && prefix != NULL && u != 0)
		ft_putstr_fd(prefix, arg->fd);
	if (arg->precisionflag)
		print_widthpad(arg->precision, nlen, '0', arg);
	if (!arg->precisionflag || arg->precision != 0 || u != 0)
		ft_putnbrbase_fd(u, base, arg->fd);
	if (arg->widthflag && arg->leftpos)
		print_widthpad(arg->width, len, ' ', arg);
	return (arg->widthflag ? ft_max(len, arg->width) : len);
}

uintmax_t	ft_uint_length(va_list *ap, t_ap *arg)
{
	uintmax_t	u;

	u = va_arg(*ap, uintmax_t);
	if (arg->length == hh)
		u = (unsigned char)u;
	else if (arg->length == h)
		u = (unsigned short int)u;
	else if (arg->length == l)
		u = (unsigned long int)u;
	else if (arg->length == ll)
		u = (unsigned long long int)u;
	else if (arg->length == j)
		u = (uintmax_t)u;
	else if (arg->length == z)
		u = (size_t)u;
	else
		u = (unsigned int)u;
	return (u);
}

int			ft_specifier_u(char **format, va_list *ap, t_ap *arg)
{
	uintmax_t	u;

	(void)format;
	u = ft_uint_length(ap, arg);
	return (ft_uint(u, arg, "0123456789", NULL));
}
