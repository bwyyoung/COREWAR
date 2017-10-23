/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:31:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/23 11:12:14 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Creates a new process. The new process will be the same except for the pc and cycles_left.
** The difference between fork and lfork is that fork will use a idx_val to increase the pc
** while lfork will just use the ind_val directly.
**
** T_DIR
*/

void			op_forker(t_env *env, t_process *process, int op)
{
	t_process	*process_cpy;
	int			index;

	if (!(process_cpy = (t_process*)malloc(sizeof(t_process))))
		ft_error_errno(NULL);
	ft_memcpy(process_cpy, process, sizeof(t_process));
	index = process->params[0].val;
	if (op == lfork)
		inc_pc(process_cpy->regs, index);
	else
		inc_pc(process_cpy->regs, get_idx_val(index));
	process_cpy->cycles_left = 0;
	add_process(env, process_cpy);
}

/*
fork

//epitech
fork:
This instruction is not followed by a parameter encoding byte.
It always takes an index and creates a new program,
which is executed from address : (PC + (first parameter % IDX_MOD)).
Fork %34 creates a new program. The new program inherits all of its father’s states.

//42
there is no argument’s coding byte, take an index, opcode 0x0c. Create a
new process that will inherit the different states of its father, except its PC, which
will be put at (PC + (1st parameter % IDX_MOD)).

*/

/*
lfork:
Same as fork, without the % IDX_MOD This operation modifies the carry.
*/