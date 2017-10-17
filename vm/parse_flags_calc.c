/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/09/08 14:49:10 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add_bonus(t_env *e, int args, int *i)
{
	if ((*i + 2) > args)
		error_exit(e, 18);
	e->bonus = 1;
	*i += 1;
}

long	get_smallest_player_id(t_env *e)
{
	int			i;
	long		small;

	i = 0;
	small = e->player[i].prog_num;
	while (++i < e->num_players)
		if (small > e->player[i].prog_num)
			small = e->player[i].prog_num;
	return (small);
}

void	check_flag_number_valid(t_env *e, char *nbr)
{
	int			i;

	i = -1;
	while (nbr[++i])
		if (!(ft_strchr(LABEL_NUMBERS, nbr[i])))
			error_exit(e, 14);
}

t_bool	check_duplicate_player(t_env *e, long nbr)
{
	long		k;

	k = -1;
	while (++k < e->num_players)
		if (nbr == e->player[k].prog_num)
			return (true);
	return (false);
}
