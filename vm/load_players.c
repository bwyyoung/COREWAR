/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:32:55 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/06 15:44:12 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			load_players(t_env *env)
{
	t_player	*player;
	uint32_t	prog_num;

	player = env->lst_players;
	prog_num = 0xffffffff;
	while (player)
	{
		if (player->prog_num == 0xffffffff)
			player->prog_num = prog_num--;
		reader(env, player, player->file_name);
		lst_process_add(env, create_process(env, player));
		env->offset += MEM_SIZE / env->num_players;
		player = player->next;
	}
}
