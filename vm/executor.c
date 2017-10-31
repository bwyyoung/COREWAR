/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:10:13 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/30 19:56:22 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					is_valid_type(uint8_t type)
{
	return (type != DIR_CODE && type != IND_CODE && type != REG_CODE);
}

int					check_types(t_process *process)
{
	int i;

	if (!op_has_type(process->op))
		return (0);
	i = 0;
	while (i < get_num_params(process->op))
	{
		if (is_valid_type(process->param_type[i++]))
			return (1);
	}
	return (0);
}
/*
** Execute the current process op.
** First check the type, if it is invalid return ;
** Then fill the param structs.
** Then execute the op by calling the right funtion
** Then inc the pc by the size of the op in bytes
**	so that the pc is no longer pointing to the op or any of its params.
**	If the op is zjmp, don't modify the pc because it has already been
**	changed by the zjmp function.
*/
void				execute_op(t_env *env, t_process *process)
{
	int	op;
	int	pc;

	pc = process->regs[0];
	op = process->op;
	process->types = get_board_val(env->board, pc + 1, 1);
	get_params(env, process, op);
	if (check_types(process))
	{
		print_verbosity_sixteen(env, process, get_op_size(process), pc);
		return (inc_pc(process, get_op_size(process)));
	}
	if (op == live)
		op_live(env, process);
	else if (op == ld || op == lld)
		op_load(env, process);
	else if (op == st || op == sti)
		op_store(env, process, pc, op);
	else if (op == add || op == sub)
		op_arithmetic(env, process);
	else if (op == and || op == or || op == xor)
		op_bitwise(env, process, op);
	else if (op == zjmp)
		op_zjmp(env, process);
	else if (op == ldi || op == lldi)
		op_index_load(env, process);
	else if (op == e_fork || op == lfork)
		op_forker(env, process, op);
	else if (op == aff)
		op_aff(env, process, pc);
	if (op != zjmp)
		inc_pc(process, get_op_size(process));
	print_verbosity_sixteen(env, process, get_op_size(process), pc);
}

/*
** A process has to wait a certain number of cycles before it
** can execute an op. (Check the op.c to see how many cycles every op costs).
** So first when an op is created it has 0 cycles. Which means that it will
**	use the value the pc is currently pointing towards as an op code.
**	If the op code is not valid (op <= 0 || op > aff) the funtion does nothing
**	but increase the pc by one to skip the invalid op.
** Then the process will get its cycle_left decreased every it runs this function
** until it is 1, at which point it executes the op. Thereby paying the cost of the op.
** After the op has been executed the cycles_left is 0 again so that the next time 
** it can try and execute the new byte that the pc is pointing towards.
**
*/
void				execute_process(t_env *env, t_process *process)
{
	int				op;

	process->last_live++;
	if (process->cycles_left == 1)
	{
		execute_op(env, process);
		process->cycles_left = 0;
	}
	else if (process->cycles_left <= 0)
	{
		op = get_board_val(env->board, process->regs[0], 1);
		if (op > 0 && op <= aff)
		{
			process->cycles_left = get_cycles(op) - 1;
			process->op = op;
		}
		else
			inc_pc(process, 1);
	}
	else
		process->cycles_left--;
}

/*
** Goes through the whole list of processes and executes them.
*/
void				execute_cycle(t_env *env)
{
	t_process		*cur_process;

	cur_process = env->lst_process;
	while (cur_process)
	{
		execute_process(env, cur_process);
		cur_process = cur_process->next;
	}
}
