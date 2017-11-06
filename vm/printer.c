/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:49:15 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/04 14:50:43 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			introduce_players(t_env *env)
{
	t_player	*player;

	P(env->g_ref, env->options[visual], "Introducing contestants...\n");
	player = env->lst_players;
	while (player)
	{
		P(env->g_ref, env->options[visual],
			"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
								player->prog_num * -1, player->size,
								player->name, player->comment);
		player = player->next;
	}
}

/*
** Declare the winner of the game.
** If no player has gotten a live then the player who was added last wins.
** So if there are four player player 4 will win.
** Else the player who has gotten the last live wins
*/

void			declare_winner(t_env *env)
{
	t_player *player;

	if (env->options[d])
		return ;
	if (!env->last_live_name)
	{
		player = env->lst_players;
		while (player->next)
			player = player->next;
		ft_printf("Contestant %d, \"%s\", has won !\n",
		player->prog_num * -1, player->name);
	}
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		env->last_live_num * -1,
		env->last_live_name);
}
