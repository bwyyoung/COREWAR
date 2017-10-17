/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/09/08 14:49:10 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

long	find_next_value(t_env *e)
{
	long		i;

	i = get_smallest_player_id(e) + 1;
	while (check_duplicate_player(e, i))
	{
		if (i == INT_MAX)
			error_exit(e, 7);
		i++;
	}
	return (i);
}

void	get_long_number(t_env *e, char *nbr, int *i, int args)
{
	long		temp;

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

void	add_player_with_number(t_env *e, char *nbr, int args, int *i)
{
	long	long_num;
	int		players;

	players = e->num_players;
	if ((*i + 3) > args)
		error_exit(e, 13);
	check_flag_number_valid(e, nbr);
	if (ft_strlen(nbr) > 15)
		error_exit(e, 7);
	long_num = ft_atoli(nbr);
	if (long_num > INT_MAX || long_num < INT_MIN)
		error_exit(e, 15);
	if (check_duplicate_player(e, long_num))
		error_exit(e, 9);
	e->player[players].prog_num = long_num;
	*i += 2;
	e->player[players].file_pos = *i;
}

void	add_player_empty(t_env *e, int *i, int players)
{
	long	value;

	if (players == 0)
		value = 1;
	else
		value = find_next_value(e);
	e->player[players].prog_num = value;
	e->player[players].file_pos = *i;
}
