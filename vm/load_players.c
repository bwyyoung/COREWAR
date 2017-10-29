/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:32:55 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/29 17:35:13 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			load_players(t_env *env)
{
	t_player	*player;
	uint32_t	prog_num;

	player = env->lst_players;
	prog_num = 0xffffffff;
	P(env->options[visual], "Introducing contestants...\n");
	while (player)
	{
		player->prog_num = prog_num--;
		reader(env, player, player->file_name);
		P(env->options[visual], "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
								player->prog_num * -1, player->size,
								player->name, player->comment);
		lst_process_add(env, create_process(env, player));
		env->offset += MEM_SIZE / env->num_players;
		player = player->next;
	}
}
