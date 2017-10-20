/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:10:13 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 12:45:39 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Make sure the type byte is valid for the current op.
** If it is not valid inc the pc by 2 to skip the op byte and the type byte
** else just return 0
*/
static int	get_types(t_process *process, uint8_t types, uint8_t op)
{
	if (is_types_invalid(op, types))
	{
		inc_pc(process->regs, 2);
		return (1);
	}
	process->types = types;
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
static void	execute_op(t_env *env, t_process *process)
{
	uint8_t			op;
	int				pc;

	pc = process->regs[0];
	op = process->op;
	if (get_types(process, env->board[(pc + 1) % MEM_SIZE], op))
		return ;
	get_params(env, process, op);
	if (op == live)
		op_live(env, process, pc);
	else if (op == ld || op == lld)
		op_load(env, process, op);
	else if (op == st || op == sti)
		op_store(env, process, pc, op);
	else if (op == add || op == sub)
		op_arithmetic(env, process, op);
	else if (op == and || op == or || op == xor)
		op_bitwise(env, process, op);
	else if (op == zjmp)
		op_zjmp(env, process, pc);
	else if (op == ldi || op == lldi)
		op_index_load(env, process, op);
	else if (op == e_fork || op == lfork)
		op_forker(env, process, pc, op);
	else if (op == aff)
		op_aff(env, process, pc);
	if (op != zjmp)
		inc_pc(process->regs, get_op_size(op, process->types));
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
static void	execute_process(t_process *process, t_env *env)
{
	uint8_t op;

	if (process->cycles_left == 1)
	{
		execute_op(env, process);
		process->cycles_left = 0;
	}
	else if (process->cycles_left <= 0)
	{
		op = env->board[process->regs[0]];
		if (op > 0 && op <= aff)
		{
			process->cycles_left = get_cycles(op) - 1;
			process->op = op;
		}
		else
			inc_pc(process->regs, 1);
	}
	else
		process->cycles_left--;
}

/*
** Goes through the whole list of processes and executes them.
*/
void		execute_cycle(t_env *env)
{
	t_list		*processes;

	processes = env->processes;
	while (processes)
	{
		execute_process(processes->content, env);
		processes = processes->next;
	}
}
