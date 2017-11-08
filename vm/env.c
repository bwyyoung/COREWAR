/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:57:43 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/08 18:02:52 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		delete_env(t_env *env)
{
	lst_process_clr(env);
	lst_players_clr(env);
	SAFE_DELETE(env);
}

void		cpy_env(t_env *dst, t_env *src)
{
	ft_bzero(dst, sizeof(t_env));
	dst->cycle_to_die = CYCLE_TO_DIE;
	dst->to_die = CYCLE_TO_DIE;
	dst->lst_process = NULL;
	dst->num_players = src->num_players;
	dst->op_tab = src->op_tab;
	dst->lst_players = src->lst_players;
	dst->lst_process = NULL;
	dst->last_live_name = NULL;
	ft_memcpy(dst->options, src->options, sizeof(int) * 10);
	dst->verbose_value = src->verbose_value;
	dst->dump_value = src->dump_value;
	dst->cycle_value = src->cycle_value;
	lst_process_clr(src);
	load_players(dst);
}
