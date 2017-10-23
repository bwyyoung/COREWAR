/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:12:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/23 11:43:37 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_env		*create_env(uint8_t *board)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		ft_error_errno(NULL);
	env->cycle_to_die = CYCLE_TO_DIE;
	env->cycles_since_check = 0;
	env->total_cycles = 0;
	env->lives_since_check = 0;
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
	env->dump_value = 0;
	env->num_players = 0;
	env->prog_num = 0xffffffff;
	env->offset = 0;
	env->to_die = CYCLE_TO_DIE;
	return (env);
}

/*
** Create a one dimensional array to represent the board and
** initialize all the bytes to zero.
*/
uint8_t		*create_board(void)
{
	uint8_t *board;

	if (!(board = (uint8_t*)malloc(MEM_SIZE)))
		ft_error_errno(NULL);
	ft_bzero(board, MEM_SIZE);
	return (board);
}

t_player	*create_player(uint32_t prog_num)
{
	t_player	*player;

	ft_printf("Creating Player %i\n", prog_num);
	if (!(player = (t_player*)malloc(sizeof(t_player))))
		ft_error_errno(NULL);
	player->lives = 0;
	if (!(player->name = ft_strnew(PROG_NAME_LENGTH)))
		ft_error_errno(NULL);	
	player->prog_num = prog_num;
	return (player);
}

t_process	*create_process(t_env *e)
{
	t_process		*process;

	process = (t_process*)malloc(sizeof(t_process));
	if (process == NULL)
		ft_error_errno(NULL);
	process->carry = 0;
	process->cycles_left = 0;
	process->name =  e->new_player->name;
	process->prog_num = e->new_player->prog_num;
	process->lives = 0;
	//ft_printf("create_process %i %i\n",e->offset, e->prog_num);
	process->regs[0] = e->offset;
	process->regs[1] = e->prog_num;
	e->i = 1;
	while (e->i++ < REG_NUMBER)
		process->regs[e->i] = 0;
	process->op = 0;
	process->process_num = e->num_processes + 1;
	return (process);
}
