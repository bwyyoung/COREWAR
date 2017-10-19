/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:41:56 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/18 20:28:05 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

static t_token		*add_label(t_token *token, t_env *env)
{
	t_label		*label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	label->name = token;
	label->addr = env->pc;
	env->labels[env->label_count] = label;
	env->label_count = env->label_count + 1;
	return (token->next);
}

static void         add_inst(t_inst *inst, t_env *env)
{
	t_inst	*tmp;

	tmp = env->inst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		env->inst = inst;
	else
		tmp->next = inst;
}

// static t_op 		*get_op_by_name(char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (i < 16)
// 	{
// 		if (!ft_strcmp(str, g_op_tab[i].op))
// 			return (&g_op_tab[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

static t_inst		*init_inst()
{
	t_inst		*inst;

	if (!(inst = (t_inst *)malloc(sizeof(t_inst))))
		return (NULL);
	inst->size = 0;
	inst->opcode = 0;
	inst->type = 0;
	inst->pcount = 0;
	inst->params = NULL;
	inst->next = NULL;
	return (inst);
}

void    		    ft_make_inst(t_token *start, t_token *end, t_env *env)
{
	t_inst		*inst;
	t_op		*op;
	int			i;

	i = 0;
	op = NULL;
	if (start->type == T_LAB)
		start = add_label(start, env);
	if (start == end)
		return ;
	inst = init_inst();
	if (start != end && start->type == 16)
	{
		op = get_op_by_name(start->value);
		inst->opcode = op->opcode;
		inst->size = op->code_byte ? inst->size + 2 : inst->size + 1;
	}
	if (start->next != end)
		inst->params = start->next;
	inst->pcount = op->pcount;
	inst->type = op->label_size ? 1 : 0;
	check_pcount(start, end, inst, env);
	check_ptype(inst, op, env);
	env->pc = env->pc + inst->size;
	add_inst(inst, env);
}
