/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/04 14:33:50 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool	add_visual(t_env *e)
{
	e->options[visual] = t_true;
	return (t_true);
}

t_bool	add_binary(t_env *e)
{
	e->options[b] = t_true;
	return (t_true);
}

t_bool	add_stealth(t_env *e)
{
	e->options[stealth] = t_true;
	return (t_true);
}

void	add_player(t_env *e, char **argv, int *i)
{
	e->new_player = lst_players_add(e, create_player(argv[*i]));
}

void	check_flag_number_valid(t_env *e, char *nbr)
{
	e->i = -1;
	while (nbr[++e->i])
		if (!(ft_strchr(LABEL_NUMBERS, nbr[e->i])))
			error_exit(e, 14);
}
