/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/21 12:49:30 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool add_visual(t_env *e)
{
	e->options[visual] = t_true;
	return (t_true);
}

t_bool add_binary(t_env *e)
{
	e->options[b] = t_true;
	return (t_true);
}

t_bool add_stealth(t_env *e)
{
	e->options[stealth] = t_true;
	return (t_true);
}

void add_player(t_env *e, char **argv, int *i)
{
	e->new_player = lst_players_add(e, create_player(e->prog_num));
	reader(e, e->offset, argv[*i]);
	// ft_printf("add_player 1\n");
	//e->new_process = create_process(e);
	lst_process_add(e, create_process(e));
//	add_process(e, e->new_process);
	// ft_printf("add_player 2\n");
//	add_player_list(e, e->new_player);
	// ft_printf("add_player 5\n");

	// ft_printf("add_player 3 %i %i %i \n", e->offset, MEM_SIZE, e->num_players);
	e->offset += MEM_SIZE / (e->num_players);
	// ft_printf("add_player 4\n");
	e->prog_num--;
	// ft_printf("add_player 6\n");
}

void	check_flag_number_valid(t_env *e, char *nbr)
{
	e->i = -1;
	while (nbr[++e->i])
		if (!(ft_strchr(LABEL_NUMBERS, nbr[e->i])))
			error_exit(e, 14);
}
