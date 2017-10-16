/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:22:45 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:22:50 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static double	ft_float_length(va_list *ap, t_ap *arg)
{
	double	f;

	f = va_arg(*ap, double);
	if (f < 0 || f == 0.0 / -1)
		arg->fneg = 1;
	if (!arg->precisionflag)
		arg->precision = 6;
	arg->precisionflag = 1;
	return (f);
}

static void		ft_intpart(long long int i, t_ap *arg, int *len)
{
	if (arg->leftpos)
		arg->widthflag = 0;
	arg->precisionflag = 0;
	if (i < 0 || arg->forcesign || arg->spacesign)
		(*len)++;
	if (arg->widthflag && !arg->padzero)
		print_widthpad(arg->width, *len, ' ', arg);
	if (arg->fneg || arg->forcesign || arg->spacesign)
	{
		if (arg->fneg)
		{
			ft_putchar_fd('-', arg->fd);
			i = -i;
		}
		else if (arg->forcesign)
			ft_putchar_fd('+', arg->fd);
		else if (!arg->forcesign && arg->spacesign)
			ft_putchar_fd(' ', arg->fd);
	}
	if (arg->widthflag && arg->padzero)
		print_widthpad(arg->width, *len, '0', arg);
	ft_putnbrbase_fd(i, "0123456789", arg->fd);
}

static void		ft_floatpart(double f, t_ap *arg, int *len)
{
	size_t				i;

	i = 0;
	arg->precisionflag = 1;
	arg->widthflag = 0;
	if (f < 0)
		f = -f;
	while (i++ < arg->precision)
		f *= 10;
	f += 0.5;
	if (arg->precisionflag && arg->precision != 0)
		ft_uint((unsigned long long)f, arg, "0123456789", NULL);
	if (arg->leftpos)
		print_widthpad(arg->width, *len, ' ', arg);
}

static int		ft_infnan(char **format, double f, t_ap *arg)
{
	int		len;

	len = 3;
	if (!(f != f) && (arg->fneg || arg->forcesign || arg->spacesign))
		len++;
	if (arg->widthflag && !arg->leftpos)
		print_widthpad(arg->width, len, ' ', arg);
	if (!(f != f) && (arg->fneg || arg->forcesign || arg->spacesign))
	{
		if (arg->fneg)
			ft_putchar_fd('-', arg->fd);
		else if (arg->forcesign)
			ft_putchar_fd('+', arg->fd);
		else if (!arg->forcesign && arg->spacesign)
			ft_putchar_fd(' ', arg->fd);
	}
	if (f == f / 0)
		ft_putstr_fd(**format == 'f' ? "inf" : "INF", arg->fd);
	else if (f != f)
		ft_putstr_fd(**format == 'f' ? "nan" : "NAN", arg->fd);
	if (arg->widthflag && arg->leftpos)
		print_widthpad(arg->width, len, ' ', arg);
	return (len);
}

int				ft_specifier_f(char **format, va_list *ap, t_ap *arg)
{
	double			f;
	long long		i;
	int				len;
	int				nlen;

	(void)format;
	f = ft_float_length(ap, arg);
	if (f == f / 0 || f != f)
		return (ft_max(arg->width, ft_infnan(format, f, arg)));
	i = (long long)f;
	f = f - i;
	nlen = i < 0 ? ft_calc_nlen(-i, "0123456789") :
		ft_calc_nlen(i, "0123456789");
	len = nlen + (arg->precisionflag ? arg->precision + 1 : 7);
	if (!arg->forcepre && arg->precisionflag && arg->precision == 0)
		len -= 1;
	ft_intpart(i, arg, &len);
	if (!(arg->precisionflag && arg->precision == 0) || arg->forcepre)
		ft_putchar_fd('.', arg->fd);
	ft_floatpart(f, arg, &len);
	return (ft_max(arg->width, len));
}
