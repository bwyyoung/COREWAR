/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:24:41 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/28 10:21:20 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdlib.h>

int		ft_specifier_n(char **format, va_list *ap, t_ap *arg)
{
	intmax_t	*n;

	(void)format;
	n = va_arg(*ap, intmax_t *);
	if (n == NULL)
		return (0);
	if (arg->length == hh)
		*n = (signed char)arg->len;
	else if (arg->length == h)
		*n = (short int)arg->len;
	else if (arg->length == l)
		*n = (long int)arg->len;
	else if (arg->length == ll)
		*n = (long long int)arg->len;
	else if (arg->length == j)
		*n = (intmax_t)arg->len;
	else if (arg->length == z)
		*n = (size_t)arg->len;
	else
		*n = (int)arg->len;
	return (0);
}
