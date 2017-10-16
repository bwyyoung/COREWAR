/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_unknown.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:25:38 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:25:51 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_unknown(char **format, va_list *ap, t_ap *arg)
{
	(void)ap;
	if (arg->widthflag && !arg->leftpos)
		print_widthpad(arg->width, 1, arg->padzero ? '0' : ' ', arg);
	ft_putchar_fd(**format, arg->fd);
	if (arg->widthflag && arg->leftpos)
		print_widthpad(arg->width, 1, ' ', arg);
	return (arg->widthflag ? ft_max(1, arg->width) : 1);
}
