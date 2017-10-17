/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:27:07 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/17 00:17:56 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			get_params(t_env *env, t_process *process, uint8_t op)
{
	uint8_t		types;
	uint8_t		type;
	uint32_t	pc;
	int			i;
	int			param_size;

	types = process->types;
	if (!op_has_type(op))
		return ;
	pc = process->regs[0];
	i = 0;
	param_size = 0;
	pc = pc + 2;
	while (types)
	{
		type = (types & 0b11000000) >> 6;
		process->params[i].type = type;
		param_size = get_arg_size(type, get_label_size(env, process));
		process->params[i].val = get_board_val(env->board, pc, param_size);
		types = types << 2;
		pc += param_size;
		i++;
	}
}

uint32_t		get_ind_val(uint8_t *board, t_process *process,
							uint32_t param_val, uint32_t read_size)
{
	uint32_t pc;
	uint32_t val;

	pc = process->regs[0];
	if (use_idx(process->op))
		val = get_board_val(board, pc + get_idx_val(param_val), read_size);
	else
		val = get_board_val(board, pc + param_val, read_size);
	return (val);
}

int				get_param_val(uint8_t *board, t_param param_struct,
								t_process *process, uint8_t read_size)
{
	int			val;
	uint8_t		type;
	uint32_t	param_val;

	type = param_struct.type;
	param_val = param_struct.val;
	if (type == REG_CODE)
		val = get_reg_val(process, param_val);
	else if (type == IND_CODE)
		val = get_ind_val(board, process, param_val, read_size);
	else
		val = param_val;
	return (val);
}