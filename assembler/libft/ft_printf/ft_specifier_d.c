/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:20:39 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:22:32 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int					ft_anyprefix(uintmax_t n, t_ap *arg, char *base,
		char *prefix)
{
	size_t		len;
	size_t		prefixlen;

	prefixlen = ft_strlen(prefix);
	len = ft_nlen_prefix(n, base, arg, NULL) + prefixlen;
	if (arg->widthflag && !arg->leftpos && !arg->padzero)
	{
		print_widthpad(arg->width, len, ' ', arg);
		prefixlen += ft_max(arg->width - len, 0);
		arg->widthflag = 0;
	}
	else if (arg->widthflag)
		arg->width -= prefixlen;
	ft_putstr_fd(prefix, arg->fd);
	return (prefixlen + ft_uint(n, arg, base, NULL));
}

static intmax_t		ft_int_length(va_list *ap, t_ap *arg)
{
	intmax_t	n;

	n = va_arg(*ap, intmax_t);
	if (arg->length == hh)
		n = (signed char)n;
	else if (arg->length == h)
		n = (short int)n;
	else if (arg->length == l)
		n = (long int)n;
	else if (arg->length == ll)
		n = (long long int)n;
	else if (arg->length == j)
		n = (intmax_t)n;
	else if (arg->length == z)
		n = (size_t)n;
	else
		n = (int)n;
	return (n);
}

int					ft_specifier_d(char **format, va_list *ap, t_ap *arg)
{
	intmax_t	n;
	char		*prefix;

	n = ft_int_length(ap, arg);
	(void)format;
	if (n < 0 || arg->forcesign || arg->spacesign)
	{
		if (n < 0)
		{
			prefix = "-";
			n = -n;
		}
		else if (arg->forcesign)
			prefix = "+";
		else if (!arg->forcesign && arg->spacesign)
			prefix = " ";
		else
			prefix = NULL;
		return (ft_anyprefix(n, arg, "0123456789", prefix));
	}
	return (ft_uint(n, arg, "0123456789", NULL));
}
