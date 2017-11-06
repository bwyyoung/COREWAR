/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:12:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/06 15:37:57 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_env			*create_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		ft_error_errno(NULL);
	env->cycle_to_die = CYCLE_TO_DIE;
	env->cycles_since_check = 0;
	env->total_cycles = 0;
	env->lives_since_check = 0;
	env->num_processes = 0;
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
	env->offset = 0;
	env->to_die = CYCLE_TO_DIE;
	env->program_size = 0;
	env->op_tab = get_op_tab();
	return (env);
}

t_player		*create_player(char *file_name, uint32_t nb)
{
	t_player	*player;

	player = (t_player*)ft_memalloc(sizeof(t_player));
	if (!player)
		ft_error_errno(NULL);
	player->lives = 0;
	player->size = 0;
	if (!(player->comment = ft_strnew(COMMENT_LENGTH)))
		ft_error_errno(NULL);
	if (!(player->name = ft_strnew(PROG_NAME_LENGTH)))
		ft_error_errno(NULL);
	player->prog_num = nb;
	player->prev = NULL;
	player->next = NULL;
	player->file_name = file_name;
	return (player);
}

t_process		*create_process(t_env *env, t_player *player)
{
	t_process		*process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		ft_error_errno(NULL);
	if (player)
		ft_bzero(process, sizeof(t_process));
	process->prev = NULL;
	process->next = NULL;
	process->regs[0] = env->offset;
	env->i = 1;
	process->vis = env->options[visual];
	process->g_ref = env->g_ref;
	process->last_live = 0;
	if (player)
	{
		process->name = player->name;
		process->prog_num = player->prog_num;
		process->regs[1] = player->prog_num;
	}
	process->process_num = env->num_processes + 1;
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
