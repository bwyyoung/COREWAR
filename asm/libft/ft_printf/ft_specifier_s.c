/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:25:07 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:25:09 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_s(char **format, va_list *ap, t_ap *arg)
{
	char	*s;
	size_t	strlen;

	if (arg->length == l)
		return (ft_specifier_ws(format, ap, arg));
	else
	{
		s = va_arg(*ap, char*);
		if (!s)
			s = "(null)";
		strlen = arg->precisionflag ? ft_strnlen(s, arg->precision) :
				ft_strlen(s);
		if (arg->widthflag && !arg->leftpos)
			print_widthpad(arg->width, strlen, arg->padzero ? '0' : ' ', arg);
		ft_putnstr_fd(s, strlen, arg->fd);
		if (arg->widthflag && arg->leftpos)
			print_widthpad(arg->width, strlen, ' ', arg);
		return (arg->widthflag ? ft_max(strlen, arg->width) : strlen);
	}
}
