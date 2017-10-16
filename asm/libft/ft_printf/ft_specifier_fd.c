/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:22:58 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:23:02 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_specifier_fd(char **format, va_list *ap, t_ap *arg)
{
	int		fd;

	(void)format;
	fd = va_arg(*ap, int);
	arg->fd = fd;
	return (0);
}
