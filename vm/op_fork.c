/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:31:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/18 10:47:41 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
Creates a new process. The new process will be the same except for the pc and cycles_left.
*/

void			op_forker(t_env *env, t_process *process, uint32_t pc, int op)
{
	t_process	*process_cpy;
	int			index;

	if (!(process_cpy = (t_process*)malloc(sizeof(t_process))))
		ft_error_errno(NULL);
	ft_memcpy(process_cpy, process, sizeof(t_process));
	index = get_board_val(env->board, pc + 1, IND_SIZE);
	if (op == lfork)
		inc_pc(process_cpy->regs, index);
	else
		inc_pc(process_cpy->regs, get_idx_val(index));
	process_cpy->cycles_left = 0;
	add_process(env, process_cpy);
}

/*
fork:
This instruction is not followed by a parameter encoding byte.
It always takes an index and creates a new program,
which is executed from address : (PC + (first parameter % IDX_MOD)).
Fork %34 creates a new program. The new program inherits all of its father’s states.

there is no argument’s coding byte, take an index, opcode 0x0c. Create a
new process that will inherit the different states of its father, except its PC, which
will be put at (PC + (1st parameter % IDX_MOD)).

T_DIR
*/

// void		op_fork(t_env *env, t_process *process, uint32_t pc)
// {
// 	forker(env, process, pc, idx);
// }

/*
lfork:
Same as fork, without the % IDX_MOD This operation modifies the carry.
*/

// void		op_lfork(t_env *env, t_process *process, uint32_t pc)
// {
// 	forker(env, process, pc, no_idx);
// }
