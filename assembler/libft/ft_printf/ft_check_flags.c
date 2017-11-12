/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:15:46 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:16:01 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*check_flags(char **format, t_ap *arg)
{
	if (**format == '-' || **format == '+' || **format == ' ' \
			|| **format == '#' || **format == '0')
	{
		if (**format == '+')
			arg->forcesign = 1;
		else if (**format == '-')
			arg->leftpos = 1;
		else if (**format == '#')
			arg->forcepre = 1;
		else if (**format == '0')
			arg->padzero = 1;
		else if (**format == ' ')
			arg->spacesign = 1;
		(*format)++;
		if (arg->leftpos)
			arg->padzero = 0;
		return (check_flags(format, arg));
	}
	else
		return (*format);
}

char	*check_width(char **format, va_list *ap, t_ap *arg)
{
	int		nb;

	while (**format == '*' || ft_isdigit(**format))
	{
		arg->width = 0;
		arg->widthflag = 1;
		if (**format == '*')
		{
			(*format)++;
			nb = va_arg(*ap, int);
			if (nb < 0)
				arg->leftpos = 1;
			arg->width = nb < 0 ? -nb : nb;
		}
		if (ft_isdigit(**format))
		{
			arg->width = 0;
			while (ft_isdigit(**format))
			{
				arg->width = (arg->width * 10) + (**format - '0');
				(*format)++;
			}
		}
	}
	return (*format);
}

char	*check_precision(char **format, va_list *ap, t_ap *arg)
{
	int		nb;

	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			(*format)++;
			if ((nb = va_arg(*ap, int)) >= 0)
			{
				arg->precision = nb;
				arg->precisionflag = 1;
			}
			return (*format);
		}
		else
		{
			arg->precisionflag = 1;
			arg->precision = 0;
			while (ft_isdigit(**format))
				arg->precision = (arg->precision * 10) + (*(*format)++ - '0');
			return (*format);
		}
	}
	return (*format);
}

char	*check_length(char **format, t_ap *arg)
{
	if (**format == 'h' && *(*format + 1) == 'h' && arg->length < 1)
	{
		arg->length = hh;
		return (*format += 2);
	}
	else if (**format == 'l' && *(*format + 1) == 'l' && arg->length < 4)
	{
		arg->length = ll;
		return (*format += 2);
	}
	else if (**format == 'h' || **format == 'l' || **format == 'j' \
			|| **format == 'z')
	{
		if (**format == 'h' && arg->length < 2)
			arg->length = h;
		else if (**format == 'l' && arg->length < 3)
			arg->length = l;
		else if (**format == 'j' && arg->length < 6)
			arg->length = j;
		else if (**format == 'z' && arg->length < 5)
			arg->length = z;
		return ((*format)++);
	}
	else
		return (*format);
}
