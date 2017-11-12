/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:26:33 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:26:38 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_x(char **format, va_list *ap, t_ap *arg)
{
	uintmax_t	x;

	x = ft_uint_length(ap, arg);
	arg->forcesign = 0;
	arg->spacesign = 0;
	if (**format == 'x')
	{
		if (!arg->forcepre || x == 0)
			return (ft_uint(x, arg, "0123456789abcdef", "0x"));
		else
			return (ft_anyprefix(x, arg, "0123456789abcdef", "0x"));
	}
	else
	{
		if (!arg->forcepre || x == 0)
			return (ft_uint(x, arg, "0123456789ABCDEF", "0X"));
		else
			return (ft_anyprefix(x, arg, "0123456789ABCDEF", "0X"));
	}
}
