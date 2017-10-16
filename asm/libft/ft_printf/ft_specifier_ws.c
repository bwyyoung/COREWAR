/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_ws.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:26:08 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:26:13 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static size_t	ft_wstrnlen(wchar_t *str, int precision, size_t i)
{
	if (*str == '\0' || precision == 0)
		return (i);
	else if (*str <= 0x7F)
		return (ft_wstrnlen(str + 1, precision - 1, i + 1));
	else if (*str <= 0x7FF && precision >= 2)
		return (ft_wstrnlen(str + 1, precision - 2, i + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (ft_wstrnlen(str + 1, precision - 3, i + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (ft_wstrnlen(str + 1, precision - 4, i + 4));
	else
		return (i);
}

static size_t	ft_wstrlen(wchar_t *str)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		str++;
	}
	return (i);
}

int				ft_specifier_ws(char **format, va_list *ap, t_ap *arg)
{
	wchar_t	*str;
	size_t	strlen;

	(void)format;
	str = va_arg(*ap, wchar_t*);
	if (str == NULL)
		str = L"(null)";
	strlen = arg->precisionflag ? ft_wstrnlen(str, arg->precision, 0) :
			ft_wstrlen(str);
	if (arg->widthflag && !arg->leftpos)
		print_widthpad(arg->width, strlen, arg->padzero ? '0' : ' ', arg);
	ft_putnwstr_fd(str, strlen, arg->fd);
	if (arg->widthflag && arg->leftpos)
		print_widthpad(arg->width, strlen, ' ', arg);
	return (arg->widthflag ? ft_max(strlen, arg->width) : strlen);
}
