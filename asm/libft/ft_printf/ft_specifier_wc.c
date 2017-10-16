/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_wc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:25:57 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:26:02 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_wc(char **format, va_list *ap, t_ap *arg)
{
	wchar_t		c;
	int			ret;

	(void)format;
	c = va_arg(*ap, wchar_t);
	if (c <= 0x7F)
		ret = 1;
	else if (c <= 0x7FF)
		ret = 2;
	else if (c <= 0xFFFF)
		ret = 3;
	else if (c <= 0x10FFFF)
		ret = 4;
	if (arg->widthflag && !arg->leftpos)
		print_widthpad(arg->width, ret, arg->padzero ? '0' : ' ', arg);
	ft_putwchar_fd(c, arg->fd);
	if (arg->widthflag && arg->leftpos)
		print_widthpad(arg->width, ret, ' ', arg);
	return (arg->widthflag ? ft_max(ret, arg->width) : ret);
}
