/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:23:16 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:23:29 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_long(char **format, va_list *ap, t_ap *arg)
{
	t_specifier		specifier;

	arg->length = l;
	return ((specifier = check_specifier(**format + 32))(format, ap, arg));
}
