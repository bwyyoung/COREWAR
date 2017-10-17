/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:18:48 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/17 00:49:46 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_basic_load(t_env *env, t_process *process, int op)
{
	uint8_t			*board;
	uint32_t		new_reg_val;
	uint32_t		read_size;
	uint8_t			type;

	board = env->board;
	type = process->params[0].type;
	new_reg_val = get_param_val(board, process->params[0], process, IND_SIZE); // should be reg_size
	set_reg_val(process, process->params[1].val, new_reg_val);
	modify_carry(process, new_reg_val);
}

/*
ld: Take a random argument and a registry. Load the value of the first argument
in the registry. Its opcode is 10 in binary and it will change the carry.

This instruction takes 2 parameters,
the 2nd of which has to be a register (not the PC)
It loads the value of the first parameter in the register.
This operation modifies the carry.
ld 34,r3 loads the REG_SIZE bytes from address (PC + (34 % IDX_MOD)) in register r3.

(T_DIR | T_IND), T_REG
label_size 4
*/
// void		op_ld(t_env *env, t_process *process)
// {
// 	basic_load(env, process, ld);
// }

/*
lld: Means long-load, so it’s opcode is obviously 13. It the same as ld, but
without % IDX_MOD. Modify the carry.
label_size 4
(T_DIR | T_IND), T_REG
*/
// void		op_lld(t_env *env, t_process *process)
// {
// 	basic_load(env, process, lld);
// }

/*
ldi:
This operation modifies the carry.
ldi 3,%4,r1 reads IND_SIZE bytes at address: (PC + (3 % IDX_MOD)),
adds 4 to this value. We will name this sum S.
Read REG_SIZE bytes at address (PC + (S % IDX_MOD)),
which are copied to r1. Parameters 1 and 2 are indexes.

ldi, ldi, as per the name, does not imply to go swimming
in chestnut cream,
even if its code is 0x0a.
Instead, it will use 2 indexes and 1 registry, adding the first
two, treating that like an address,
reading a value of a registry’s size and putting it on the third.

(T_REG | T_DIR | T_IND) , (T_DIR | T_REG), T_REG
label size 2

Needs fixing like load
*/

void		op_index_load(t_env *env, t_process *process, int op)
{
	int			index1;
	int			index2;
	int			index_sum;
	int			new_reg_val;

	index1 = get_param_val(env->board, process->params[0],
							process, IND_SIZE);
	index2 = get_param_val(env->board, process->params[1],
							process, IND_SIZE);
	index_sum = index1 + index2;
	new_reg_val = get_ind_val(env->board, process, index_sum, REG_SIZE);
	set_reg_val(process, process->params[2].val, new_reg_val);
	modify_carry(process, new_reg_val);
}
						

// void		op_ldi(t_env *env, t_process *process)
// {
// 	index_load(env, process, idx);
// }

/*
lldi:
Same as ldi, without the % IDX_MOD This operation modifies the carry.
*/

// void		op_lldi(t_env *env, t_process *process)
// {
// 	index_load(env, process, no_idx);
// }