/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:20:25 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:20:32 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_c(char **format, va_list *ap, t_ap *arg)
{
	int		c;

	if (arg->length == l)
		return (ft_specifier_wc(format, ap, arg));
	else
	{
		c = va_arg(*ap, int);
		if (arg->widthflag && !arg->leftpos)
			print_widthpad(arg->width, 1, arg->padzero ? '0' : ' ', arg);
		ft_putchar_fd(c, arg->fd);
		if (arg->widthflag && arg->leftpos)
			print_widthpad(arg->width, 1, ' ', arg);
		return (arg->widthflag ? ft_max(1, arg->width) : 1);
	}
}
