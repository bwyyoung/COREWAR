/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:58:47 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:10:32 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static char		*check_all(char **format, va_list *ap, t_ap *arg)
{
	if (!check_flags(format, arg))
		return (0);
	if (!check_width(format, ap, arg))
		return (0);
	if (!check_precision(format, ap, arg))
		return (0);
	if (!check_length(format, arg))
		return (0);
	return (*format);
}

static int		check(char **format, va_list *ap, t_ap *arg, size_t c)
{
	int			ret;
	int			fd;
	t_specifier	specifier;

	fd = arg->fd;
	ft_bzero(arg, sizeof(*arg));
	arg->fd = fd;
	if (!*(++*format))
		return (0);
	arg->len = c;
	while (**format == '0' || **format == '-' || **format == ' ' ||
			**format == '+' || **format == '#' || **format == 'h' ||
			**format == 'l' || **format == 'j' || **format == 'z' ||
			**format == '.' || **format == '*' || ft_isdigit(**format))
		if (!check_all(format, ap, arg))
			return (-1);
	if (!**format)
		return (0);
	if (!(specifier = check_specifier(**format)))
		specifier = ft_specifier_unknown;
	ret = specifier(format, ap, arg);
	(*format)++;
	return (ret);
}

static int		ft_printf_new(const char *format, va_list *ap, size_t c,
		t_ap *arg)
{
	char	*next;
	int		len;

	next = ft_strchr(format, '%');
	if (!*format)
		return (c);
	if (!next)
	{
		ft_putstr_fd(format, arg->fd);
		return (c + ft_strlen(format));
	}
	else if (next > format)
	{
		ft_putnstr_fd(format, next - format, arg->fd);
		return (ft_printf_new(next, ap, c + (next - format), arg));
	}
	else
	{
		if ((len = check((char **)&format, ap, arg, c)) == -1)
			return (-1);
		else
			return (ft_printf_new(format, ap, c + len, arg));
	}
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_ap		arg;
	int			ret;

	va_start(ap, format);
	arg.fd = 1;
	ret = ft_printf_new(format, &ap, 0, &arg);
	va_end(ap);
	return (ret);
}
