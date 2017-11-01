/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:18:48 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/30 18:04:28 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process, int op, int new_reg_val)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s %d r%d\n", process->process_num,
								get_op_name(op),
								new_reg_val,
								process->param_val[1]);
}

/*
** ld: Take a param and load it into a registry(P2)
** lld: The same as ld but doesn't use IDX_MOD
** (T_DIR | T_IND), T_REG
*/

void		op_load(t_env *env, t_process *process)
{
	int		new_reg_val;

	if (process->param_type[0] == REG_CODE || process->param_type[1] != REG_CODE)
		return ;
	if (check_param_reg_nums(process, 0, 1, 0))
		return ;
	new_reg_val = get_param_val(env->board, 0, process);
	set_reg_val(process, process->param_val[1], new_reg_val);
	modify_carry(process, new_reg_val);
	print_verbosity_four(env, process, process->op, new_reg_val);
}

/*
// 42
ld: Take a random argument and a registry. Load the value of the first argument
in the registry. Its opcode is 10 in binary and it will change the carry.

// epitech
This instruction takes 2 parameters,
the 2nd of which has to be a register (not the PC)
It loads the value of the first parameter in the register.
This operation modifies the carry.
ld 34,r3 loads the REG_SIZE bytes from address (PC + (34 % IDX_MOD)) in register r3.

// epitech
lld: Means long-load, so it’s opcode is obviously 13. It the same as ld, but
without % IDX_MOD. Modify the carry.
label_size 4
*/

static void	print_index_verbosity_four(t_env *env, t_process *process, int pc, t_index_info *index_info)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s ", process->process_num,
								get_op_name(process->op));
	P(env->g_ref, env->options[visual], "%d ", index_info->index1);
	P(env->g_ref, env->options[visual], "%d ", index_info->index2);
	P(env->g_ref, env->options[visual], "r%d\n", process->param_val[2]);
	P(env->g_ref, env->options[visual], "       | -> load from %d + %d = %d",
				index_info->index1,
				index_info->index2,
				index_info->index_sum);
	if (process->op == lldi)
		P(env->g_ref, env->options[visual], " (with pc %d)\n", pc + index_info->index_sum);
	else
		P(env->g_ref, env->options[visual], " (with pc and mod %d)\n",
		(pc + (index_info->index_sum % IDX_MOD)) % MEM_SIZE);
}

static int	get_new_reg_val(t_env *env, t_process *process, int index_sum)
{
	if (process->op == ldi)
		return (get_board_val(env->board, (process->regs[0]
			+ (index_sum % IDX_MOD)) % MEM_SIZE, REG_SIZE));
	else
		return (get_board_val(env->board, (process->regs[0]
			+ index_sum) % MEM_SIZE, REG_SIZE));
}

/*
** ldi adds its params P1 and P2 and converts that sum to an idx_val.
** It then uses the idx_val to read REG_SIZE bytes from the board.
** It then loads the val it has read from the board into the P3 register.
**
** lldi works the same but it does not convert the val into an idx_val.
**
** (T_REG | T_DIR | T_IND) , (T_DIR | T_REG), T_REG
*/
void		op_index_load(t_env *env, t_process *process)
{
	int				index1;
	int				index2;
	int				index_sum;
	int				new_reg_val;
	t_index_info	*index_info;

	if (process->param_type[1] == IND_CODE || process->param_type[2] != REG_CODE)
		return ;
	if (check_param_reg_nums(process, 1, 1, 1))
		return ;
	index1 = get_param_val(env->board, 0, process);
	index2 = get_param_val(env->board, 1, process);
	index_sum = index1 + index2;
	new_reg_val = get_new_reg_val(env, process, index_sum);
	set_reg_val(process, process->param_val[2], new_reg_val);
	modify_carry(process, new_reg_val);
	index_info = create_index_info(index1, index2, index_sum);
	print_index_verbosity_four(env, process, process->regs[0], index_info);
	SAFE_DELETE(index_info);
}

/*
// epitech
ldi:
This operation modifies the carry.
ldi 3,%4,r1 reads IND_SIZE bytes at address: (PC + (3 % IDX_MOD)),
adds 4 to this value. We will name this sum S.
Read REG_SIZE bytes at address (PC + (S % IDX_MOD)),
which are copied to r1. Parameters 1 and 2 are indexes.

// 42
ldi, ldi, as per the name, does not imply to go swimming
in chestnut cream,
even if its code is 0x0a.
Instead, it will use 2 indexes and 1 registry, adding the first
two, treating that like an address,
reading a value of a registry’s size and putting it on the third.


lldi:
Same as ldi, without the % IDX_MOD This operation modifies the carry.
*/
