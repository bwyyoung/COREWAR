/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:27:07 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/28 15:17:00 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
/*
** Every process has an array of three param structs.
** A param struct contains an uint8_t type, and an uint32_t val.
** Example:
**			AND op
**			op type	param1	param2			param3
**			06 64	01		00 00 00 05		03
**			
**			After using get_params the param structs will look like this.
**			param[0]	type	REG_CODE (01)
**						val		1
**			param[1]	type	DIR_CODE (11)
**						val		5
**			param[2]	type	REG_CODE (01)
**						val		3
*/

void			get_no_type_val(t_env *env, t_process *process,
								uint8_t op, uint32_t pc)
{
	uint32_t val;

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
	uint32_t	pc;
	int			i;
	int			param_size;

	types = process->types;
	pc = process->regs[0];
	if (!op_has_type(op))
		return (get_no_type_val(env, process, op, pc));
	i = 0;
	param_size = 0;
	pc = pc + 2;
	while (i < 3)
	{
		type = (types & 0b11000000) >> 6;
		process->param_type[i] = type;
		param_size = get_param_size(type, get_label_size(op));
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
uint32_t			get_ind_val(uint8_t *board, t_process *process,
							int16_t param_val, uint32_t read_size)
{
	uint32_t	pc;
	uint32_t	val;

	pc = process->regs[0];
	if (op_uses_idx(process->op))
		val = get_board_val(board, pc + get_idx_val(param_val), read_size);
	else
		val = get_board_val(board, pc + param_val, read_size);
	return (val);
}

/*
** Get the value that the param_val represents.
** If the param_val is a registry(REG_VAL), get the value inside that registry.
** If the param_val is an indirect val(IND_VAL), get the value from the board.
** If the param_val is a direct val(DIR_VAL), return the param_val.
*/
uint32_t		get_param_val(uint8_t *board, int which_param,
								t_process *process, uint8_t read_size)
{
	uint32_t	val;
	uint8_t		param_type;
	uint32_t	param_val;

	param_val = process->param_val[which_param];
	param_type = process->param_type[which_param];
	if (param_type == REG_CODE)
		val = get_reg_val(process, param_val);
	else if (param_type == IND_CODE)
		val = get_ind_val(board, process, (int16_t)param_val, read_size);
	else
		val = (get_label_size(process->op) == 4) ? param_val : (int16_t) param_val;
	return (val);
}

int				check_param_reg_nums(t_process *process, int p0, int p1, int p2)
{
	if (p0 && process->param_type[0] == REG_CODE
		&& is_reg_num_invalid(process->param_val[0]))
			return (1);
	if (p1 && process->param_type[1] == REG_CODE
		&& is_reg_num_invalid(process->param_val[1]))
			return (1);
	if (p2 && process->param_type[2] == REG_CODE 
		&& is_reg_num_invalid(process->param_val[2]))
			return (1);
	return (0);
}
