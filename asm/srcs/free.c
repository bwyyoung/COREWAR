/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:23:23 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/18 20:39:04 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

static void		free_tokens(t_token *token)
{
	t_token		*tmp;

	while (token)
	{
		free(token->pos);
		free(token->value);
		tmp = token->next;
		free(token);
		token = tmp;
	}
}

static void		free_labels(t_label **labels, int count)
{
	int		i;

	i = 0;
	while (i < count)
		free(labels[i++]);
	free(labels);
}

static void		free_inst(t_inst *inst)
{
	t_inst	*tmp;

	while (inst)
	{
		tmp = inst->next;
		free(inst);
		inst = tmp;
	}
}

void			free_env(t_env *env)
{
	if (env->header)
		free(env->header);
	if (env->token)
		free_tokens(env->token);
	if	(env->labels)
		free_labels(env->labels, env->label_count);
	if (env->inst)
		free_inst(env->inst);
	if (env->str)
		free(env->str);
	if (env->filename)
		free(env->filename);
}
