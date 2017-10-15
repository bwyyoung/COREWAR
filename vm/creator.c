/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:12:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/12 14:55:10 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_env		*create_env(uint8_t *board)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		exit(ft_printf("malloc failed\n"));
	env->cycle_to_die = CYCLE_TO_DIE;
	env->cycles_since_check = 0;
	env->total_cycles = 0;
	env->total_lives = 0;
	env->num_processes = 0;
	env->board = board;
	env->processes = NULL;
	env->players = NULL;
	env->last_live_num = 0;
	env->last_live_name = NULL;
	env->checks = 0;
	env->options[0] = 0;
	env->options[1] = 0;
	env->options[2] = 0;
	env->options[3] = 0;
	env->options[4] = 0;
	env->option_num = 0;
	env->num_players = 0;
	env->to_die = CYCLE_TO_DIE;
	return (env);
}

uint8_t		*create_board(void)
{
	uint8_t *board;

	if (!(board = (uint8_t*)malloc(MEM_SIZE)))
		exit(ft_printf("malloc failed\n"));
	ft_bzero(board, MEM_SIZE);
	return (board);
}

t_player	*create_player(uint32_t prog_num)
{
	t_player	*player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		exit(ft_printf("player malloc failed\n"));
	player->lives = 0;
	player->name = ft_strnew(128);
	player->prog_num = prog_num;
	player->is_alive = 1;
	return (player);
}

t_process	*create_process(int offset, uint32_t prog_num, char *player_name)
{
	t_process *process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		exit(ft_printf("process malloc failed\n"));
	process->carry = 0;
	process->cycles_left = 0;
	process->name = player_name;
	process->prog_num = prog_num;
	process->lives = 0;
	process->regs[0] = offset;
	process->regs[1] = prog_num;
	return (process);
}
