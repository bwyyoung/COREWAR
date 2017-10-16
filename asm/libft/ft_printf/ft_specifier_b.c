/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:20:13 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:20:17 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_b(char **format, va_list *ap, t_ap *arg)
{
	uintmax_t	b;

	(void)format;
	b = ft_uint_length(ap, arg);
	return (ft_uint(b, arg, "01", NULL));
}
