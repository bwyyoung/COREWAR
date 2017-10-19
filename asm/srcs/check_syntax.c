/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:52:09 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/18 18:54:50 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

static void		type_byte(t_inst *inst, t_token *param, int pcount)
{
	unsigned char	type;
	int				bit;
	int				i;

	type = 0;
	bit = 1;
	i = 1;
	while (i++ < pcount)
		bit = bit + 2;
	if (param->type == T_REG)
		type = type | 1 << (8 - bit - 1);
	else if (param->type == T_DIR)
		type = type | 1 << (8 - bit);
	else if (param->type == T_IND)
		type = type | 1 << (8 - bit) | 1 << (8 - bit - 1);
	inst->type = inst->type | type;
}

void    		check_ptype(t_inst *inst, t_op *op, t_env *env)
{
	char	ptypes[inst->pcount];
	char	tmp;
	t_token	*param;
	int		i;

	i = 0;
	param = inst->params;
	while (i < op->pcount)
	{
		tmp = 0;
		ptypes[i] = param->type;
		tmp = ptypes[i] | op->ptypes[i];
		if (tmp != op->ptypes[i])
			ft_error(param, env, "Parameter type not valid.");
		if (op->code_byte)
			type_byte(inst, param, i + 1);
		i++;
		if (i < op->pcount)
			param = param->next->next;
	}
}

void    		check_pcount(t_token *start, t_token *end, t_inst *inst, t_env *env)
{
	int		i;

	i = 0;
	while (i < inst->pcount && start->next != end)
	{
		start = start->next;
		if (start->type == T_REG)
			inst->size = inst->size + 1;
		else if (start->type == T_IND)
			inst->size = inst->size + 2;
		else
		{
			if (inst->type)
				inst->size = inst->size + 2;
			else
				inst->size = inst->size + 4;
		}
		i++;
		if (i < inst->pcount && start->next != end)
			start = start->next;
	}
	inst->type = 0;
	if (start->next != end || i != inst->pcount)
		ft_error(start, env, "Parameters count not matching.");
}
