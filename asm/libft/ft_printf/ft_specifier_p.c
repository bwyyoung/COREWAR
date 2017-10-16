/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:24:59 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:25:01 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_p(char **format, va_list *ap, t_ap *arg)
{
	uintmax_t	p;

	(void)format;
	p = va_arg(*ap, unsigned long int);
	return (ft_anyprefix(p, arg, "0123456789abcdef", "0x"));
}
