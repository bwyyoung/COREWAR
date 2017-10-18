/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:16:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/18 17:37:54 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** st takes a register and stores its value either on the board or in another registry.
**
** T_REG, (T_IND | T_REG)
*/

static void	op_st(t_env *env, t_process *process, uint32_t pc)
{
	uint32_t	reg_num;
	int			reg_val;
	int			param_val;

	reg_num = process->params[0].val;
	if (valid_reg_num(reg_num))
	{
		reg_val = get_reg_val(process, reg_num);
		param_val = process->params[1].val;
		if (process->params[1].type == REG_CODE)
			set_reg_val(process, param_val, reg_val);
		else
			set_board_val(env->board, pc + get_idx_val(param_val), REG_SIZE, reg_val);
	}
}
/*
//42
st: take a registry and a registry or an indirect and store the value of the registry
toward a second argument. Its opcode is 0x03. For example, st r1, 42 store the
value of r1 at the address (PC + (42 % IDX_MOD))

//epitech
This instruction takes 2 parameters.
It stores (REG_SIZE bytes) the value of the first argument
(always a register) in the second.
st r4,34 stores the value of r4 at the address
(PC + (34 % IDX_MOD)) st r3,r8 copies r3 in r8
*/


/*
** sti adds its params P2 and P3 and converts that sum to an idx_val.
** It then uses that idx_val as an index to decide where on the board
** to write the value of P1 (REG).
**
** T_REG, (T_REG | T_DIR | T_IND), (T_DIR | T_REG)
*/

static void	op_sti(t_env *env, t_process *process, uint32_t pc)
{
	int			reg_val;
	int			reg_num;
	int			index1;
	int			index2;
	int			index_sum;

	reg_num = process->params[0].val;
	if (valid_reg_num(reg_num))
	{
		reg_val = get_reg_val(process, reg_num);
		index1 = get_param_val(env->board, process->params[1], process, REG_SIZE);
		index2 = get_param_val(env->board, process->params[2], process, REG_SIZE);
		index_sum = index1 + index2;
		set_board_val(env->board, pc + get_idx_val(index_sum), REG_SIZE, reg_val);
	}
}

/*
//42
sti r2,%4,%5 sti copies REG_SIZE bytes of r2 at address (4 + 5)
Parameters 2 and 3 are indexes.
If they are, in fact, registers, we’ll use their contents as indexes.

//epitech
Opcode 11. Take a registry, and two indexes (potentially registries)
add the two indexes, and use this result as an address
where the value of the first parameter
will be copied.
*/

void	op_store(t_env *env, t_process *process, uint32_t pc, uint8_t op)
{
	if (op == sti)
		op_sti(env, process, pc);
	else
		op_st(env, process, pc);
}
