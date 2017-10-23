/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/23 11:42:56 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

long	verify_number(t_env *e, char *nbr)
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

t_bool	get_dump_number(t_env *e, char *nbr, int *i, int argc) /// -d
{
	e->options[d] = true;
	if ((*i + 2) > argc)
		error_exit(e, 11);
	*i += 1;
	e->dump_value = verify_number(e, nbr);
	return (true);
}

t_bool	get_cycle_number(t_env *e, char *nbr, int *i, int argc) /// -s
{
	// ft_printf("get_cycle_number 1\n");
	e->options[s] = true;
	// ft_printf("get_cycle_number 2\n");

	if ((*i + 2) > argc)
		error_exit(e, 11);
	// ft_printf("get_cycle_number 3\n");

	*i += 1;
	// ft_printf("get_cycle_number 4\n");

	e->cycle_value = verify_number(e, nbr);
	// ft_printf("get_cycle_number 5\n");

	return (true);
}

t_bool	get_verbose_level(t_env *e, char *nbr, int *i, int argc)
{
	e->options[v] = true;
	// ft_printf("get_verbose_level 1\n");
	if ((*i + 2) > argc)
		error_exit(e, 11);
	// ft_printf("get_verbose_level 2\n");
	// ft_printf("get_verbose_level 3 %s %i\n", nbr, !ft_strcmp(nbr, "0"));
	if (!ft_strcmp(nbr, "0") || !ft_strcmp(nbr, "1") || !ft_strcmp(nbr, "2") ||
	 !ft_strcmp(nbr, "4") || !ft_strcmp(nbr, "8") || !ft_strcmp(nbr, "16"))
		e->verbose_value = verify_number(e, nbr);
	else
		error_exit(e, 13);
	*i += 1;
	// ft_printf("get_verbose_level 4\n");
	return (true);
}
