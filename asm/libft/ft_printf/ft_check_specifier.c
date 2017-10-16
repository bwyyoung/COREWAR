/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:07:15 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/25 19:07:30 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void		init_array(t_specifier *specifier)
{
	specifier['s'] = &ft_specifier_s;
	specifier['S'] = &ft_specifier_ws;
	specifier['c'] = &ft_specifier_c;
	specifier['C'] = &ft_specifier_wc;
	specifier['u'] = &ft_specifier_u;
	specifier['U'] = &ft_specifier_long;
	specifier['d'] = &ft_specifier_d;
	specifier['D'] = &ft_specifier_long;
	specifier['i'] = &ft_specifier_d;
	specifier['x'] = &ft_specifier_x;
	specifier['X'] = &ft_specifier_x;
	specifier['o'] = &ft_specifier_o;
	specifier['O'] = &ft_specifier_long;
	specifier['p'] = &ft_specifier_p;
	specifier['n'] = &ft_specifier_n;
	specifier['b'] = &ft_specifier_b;
	specifier['T'] = &ft_specifier_fd;
	specifier['f'] = &ft_specifier_f;
	specifier['F'] = &ft_specifier_f;
}

t_specifier		check_specifier(char c)
{
	static t_specifier	*specifier = NULL;

	if (!specifier)
	{
		if ((specifier = ft_memalloc(sizeof(*specifier) * 256)) != NULL)
			init_array(specifier);
	}
	return (specifier[(int)c]);
}
