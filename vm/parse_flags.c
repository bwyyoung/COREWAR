/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/10 13:48:03 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

long		verify_number(t_env *e, char *nbr)
{
	long		temp;

	check_flag_number_valid(e, nbr);
	if (ft_strlen(nbr) > 15)
		error_exit(e, 12);
	temp = ft_atoli(nbr);
	if (temp > INT_MAX || temp < INT_MIN)
		error_exit(e, 15);
	return (temp);
}

uint32_t	get_player_number(t_env *e, char *nbr, int *i, int argc)
{
	if ((*i + 2) > argc)
		error_exit(e, 11);
	*i += 2;
	return (verify_number(e, nbr));
}

t_bool		get_dump_number(t_env *e, char *nbr, int *i, int argc)
{
	e->options[d] = t_true;
	if ((*i + 2) > argc)
		error_exit(e, 11);
	*i += 1;
	e->dump_value = verify_number(e, nbr);
	return (t_true);
}

t_bool		get_cycle_number(t_env *e, char *nbr, int *i, int argc)
{
	e->options[s] = t_true;
	if ((*i + 2) > argc)
		error_exit(e, 11);
	*i += 1;
	e->cycle_value = verify_number(e, nbr);
	return (t_true);
}

t_bool		get_verbose_level(t_env *e, char *nbr, int *i, int argc)
{
	e->options[v] = t_true;
	if ((*i + 2) > argc)
		error_exit(e, 11);
	if (!ft_strcmp(nbr, "0") || !ft_strcmp(nbr, "1") || !ft_strcmp(nbr, "2") ||
		!ft_strcmp(nbr, "4") || !ft_strcmp(nbr, "8") || !ft_strcmp(nbr, "16"))
		e->verbose_value = verify_number(e, nbr);
	else
		error_exit(e, 13);
	*i += 1;
	return (t_true);
}
