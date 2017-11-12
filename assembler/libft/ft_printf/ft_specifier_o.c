/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_o.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:24:49 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:24:52 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_o(char **format, va_list *ap, t_ap *arg)
{
	uintmax_t	o;
	size_t		nlen;

	(void)format;
	o = ft_uint_length(ap, arg);
	nlen = ft_calc_nlen(o, "01234567");
	if (arg->forcepre && o != 0)
	{
		arg->precision = ft_max(arg->precision, nlen + 1);
		arg->precisionflag = 1;
	}
	else if (arg->forcepre)
	{
		arg->precisionflag = 1;
		arg->precision = 0;
		return (ft_anyprefix(o, arg, "01234567", "0"));
	}
	return (ft_uint(o, arg, "01234567", NULL));
}
