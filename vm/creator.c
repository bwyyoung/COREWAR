/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:12:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/29 16:11:51 by dengstra         ###   ########.fr       */
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
	env->lst_process = NULL;
	env->lst_players = NULL;
	env->last_live_num = 0;
	env->last_live_name = NULL;
	env->checks = 0;
	env->i = -1;
	while (++env->i < 7)
		env->options[env->i] = t_false;
	env->dump_value = 0;
	env->num_players = 0;
	env->prog_num = 0xffffffff;
	env->offset = 0;
	env->to_die = CYCLE_TO_DIE;
	env->program_size = 0;
	ft_bzero(env->prog_num_board, MEM_SIZE);
	// env->first = NULL;
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

t_player	*create_player(char *file_name)
{
	t_player	*player;

	player = (t_player*)malloc(sizeof(t_player));
	if (!player)
		ft_error_errno(NULL);
	player->lives = 0;
	// if (!(player->header = (t_header*)malloc(sizeof(t_header))))
		// ft_error_errno(NULL);
	// player->header->magic = 0;
	// player->header->prog_size = 0;
	player->size = 0;
	if (!(player->comment = ft_strnew(COMMENT_LENGTH)))
		ft_error_errno(NULL);
	if (!(player->name = ft_strnew(PROG_NAME_LENGTH)))
		ft_error_errno(NULL);
	player->prog_num = 0;
	player->prev = NULL;
	player->next = NULL;
	player->file_name = file_name;
	return (player);
}

t_process	*create_process(t_env *e)
{
	t_process		*process;

	process = (t_process*)malloc(sizeof(t_process));
	if (process == NULL)
		ft_error_errno(NULL);
	process->prev = NULL;
	process->next = NULL;
	process->types = 0;
	process->regs[0] = e->offset;
	process->regs[1] = e->prog_num;
	e->i = 1;
	while (e->i++ < REG_NUMBER)
		process->regs[e->i] = 0;
	process->param_type[0] = 0;
	process->param_type[1] = 0;
	process->param_type[2] = 0;
	process->param_val[0] = 0;
	process->param_val[1] = 0;
	process->param_val[2] = 0;
	process->carry = 0;
	process->cycles_left = 0;
	process->name = e->new_player->name;
	process->prog_num = e->new_player->prog_num;
	process->lives = 0;
	process->op = 0;
	process->process_num = e->num_processes + 1;
	process->last_live = 0;
	// process->old_pc = 0;
	return (process);
}

t_index_info	*create_index_info(int index1, int index2, int index_sum)
{
	t_index_info *index_info;

	if (!(index_info = (t_index_info*)malloc(sizeof(t_index_info))))
		ft_error_errno(NULL);
	index_info->index1 = index1;
	index_info->index2 = index2;
	index_info->index_sum = index_sum;
	return (index_info);
}
