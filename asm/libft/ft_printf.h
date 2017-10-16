/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:00:24 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 20:03:06 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct	s_ap
{
	int		leftpos;
	int		forcesign;
	int		spacesign;
	int		forcepre;
	int		padzero;
	int		widthflag;
	size_t	width;
	int		precisionflag;
	size_t	precision;
	int		lengthflag;
	size_t	len;
	int		fd;
	int		fneg;
	enum {
		none,
		hh,
		h,
		l,
		ll,
		z,
		j
	}		length;
}				t_ap;
typedef int		(*t_specifier)(char **, va_list *, t_ap *);
t_specifier		check_specifier(char c);
void			print_widthpad(int width, int strlen, char c, t_ap *arg);
uintmax_t		ft_uint_length(va_list *ap, t_ap *arg);
size_t			ft_calc_nlen(uintmax_t n, char *base);
size_t			ft_nlen_prefix(uintmax_t u, char *base, t_ap *arg, char *pre);
int				ft_uint(uintmax_t u, t_ap *arg, char *base, char *prefix);
int				ft_anyprefix(uintmax_t n, t_ap *arg, char *base, char *prefix);
char			*check_flags(char **format, t_ap *arg);
char			*check_width(char **format, va_list *ap, t_ap *arg);
char			*check_precision(char **format, va_list *ap, t_ap *arg);
char			*check_length(char **format, t_ap *arg);
int				ft_specifier_s(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_ws(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_u(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_d(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_c(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_wc(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_x(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_o(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_long(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_p(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_n(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_b(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_fd(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_f(char **format, va_list *ap, t_ap *arg);
int				ft_specifier_unknown(char **format, va_list *ap, t_ap *arg);

#endif
