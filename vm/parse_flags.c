/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/18 09:59:59 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_dump_number(t_env *e, char *nbr, int *i, int args)
{
	long		temp;

	e->options[d] = 1;
	if ((*i + 3) > args)
		error_exit(e, 11);
	*i += 1;
	e->dump = 1;
	check_flag_number_valid(e, nbr);
	if (ft_strlen(nbr) > 15)
		error_exit(e, 12);
	temp = ft_atoli(nbr);
	if (temp > INT_MAX || temp < 0)
		error_exit(e, 19);
	else
		e->dump_value = temp;
	*i += 1;
}

void	get_cycle_number(t_env *e, char *nbr, int *i, int args)
{

}