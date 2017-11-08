/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:27:07 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/07 14:17:12 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			get_no_type_val(t_env *env, t_process *process,
								uint8_t op, int pc)
{
	int val;

	if (op == e_fork || op == lfork)
		val = get_board_val(env->board, pc + 1, IND_SIZE);
	else if (op == live)
		val = get_board_val(env->board, pc + 1, 4);
	else
		val = get_board_val(env->board, pc + 1, IND_SIZE);
	process->param_val[0] = val;
}

void			get_params(t_env *env, t_process *process, int op)
{
	uint8_t		types;
	uint8_t		type;
	int			pc;
	int			i;
	int			param_size;

	types = process->types;
	pc = process->regs[0];
	if (!env->op_tab[op].has_type)
		return (get_no_type_val(env, process, op, pc));
	i = 0;
	param_size = 0;
	pc = pc + 2;
	while (i < 3)
	{
		type = (types & 0b11000000) >> 6;
		process->param_type[i] = type;
		param_size = get_param_size(type, env->op_tab[op].label_size);
		process->param_val[i] = get_board_val(env->board, pc, param_size);
		types = types << 2;
		pc += param_size;
		i++;
	}
}

/*
** This function will get a value from the board.
** It will either get the val with the param_val itself
** or by converting it to a idx_val depending on the op.
** It uses the function op_uses_idx to do that which is
** defined in the op.c.
** IND_VALs are always relative to the pc,
** so the val is always added to the pc.
** The function will read a val of size read_size.
** This is because different ops will need different size vals
** for example one op will want a REG_VAL of size 4 and another
** will want a IND_VAL of size 2.
*/

int				get_ind_val(t_env *env, t_process *process, int16_t param_val)
{
	int	pc;
	int	val;
	int read_size;

	read_size = (process->op == lld) ? 2 : 4;
	pc = process->regs[0];
	if (env->op_tab[process->op].use_idx)
		val = get_board_val(env->board, pc + ((int16_t)param_val % IDX_MOD),
							read_size);
	else
		val = get_board_val(env->board, pc + param_val, read_size);
	return (val);
}

/*
** Get the value that the param_val represents.
** If the param_val is a registry(REG_VAL), get the value inside that registry.
** If the param_val is an indirect val(IND_VAL), get the value from the board.
** If the param_val is a direct val(DIR_VAL), return the param_val.
*/

int				get_param_val(t_env *env, t_process *process, int which_param)
{
	int		val;
	uint8_t	param_type;
	int		param_val;

	param_val = process->param_val[which_param];
	param_type = process->param_type[which_param];
	if (param_type == REG_CODE)
		val = get_reg_val(process, param_val);
	else if (param_type == IND_CODE)
		val = get_ind_val(env, process, (int16_t)param_val);
	else
	{
		val = (env->op_tab[process->op].label_size == 4)
										? param_val : (int16_t)param_val;
	}
	return (val);
}

int				check_param_reg_nums(t_process *process)
{
	return ((process->param_type[0] == REG_CODE
			&& is_reg_num_invalid(process->param_val[0]))
		|| (process->param_type[1] == REG_CODE
			&& is_reg_num_invalid(process->param_val[1]))
		|| (process->param_type[2] == REG_CODE
			&& is_reg_num_invalid(process->param_val[2])));
}
