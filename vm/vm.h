/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:37:30 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 15:33:33 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft/libft.h"
# include "op.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# define LABEL_NUMBERS "-0123456789"

enum
{
	zero,
	live,
	ld,
	st,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	e_fork,
	lld,
	lldi,
	lfork,
	aff
}					e_ops;

enum
{
	d,
	s,
	visual,
	v,
	b,
	stealth
}					e_options;

typedef struct		s_player
{
	int				lives;
	char			*name;
	long			prog_num;
	int				file_pos;
}					t_player;

typedef struct		s_env
{
	int				cycle_to_die;
	int				cycles_since_check;
	long			total_cycles;
	int				lives_since_check;
	int				num_processes;
	uint8_t			*board;
	t_list			*processes;
	t_list			*players;
	int				last_live_num;
	char			*last_live_name;
	int				checks;
	int				options[6];
	int				num_players;
	int				to_die;
	long			dump_value;
	long			cycle_value;
	long			verbose_value;
	t_player		*new_player;
	uint32_t		prog_num;
	int				offset;
	//dump_value == options_num (OLD)
	t_player		player[MAX_PLAYERS + 1];
	int				i;
	int				j;
	int				k;
	int				x;
	int				y;
	int				z;
}					t_env;

// typedef struct		s_reg
// {
// 	uint8_t			num[REG_SIZE];
// }					t_reg;

typedef struct		s_params
{
	uint8_t			type;
	uint32_t		val;
}					t_param;

typedef struct		s_process
{
	uint8_t			types;
	uint32_t		regs[REG_NUMBER];	// should be REG_SIZE datatype
	t_param			params[3];
	int				carry;
	int				cycles_left;
	char			*name;
	uint32_t		prog_num;
	int				lives;
	int				op;
}					t_process;

uint32_t			get_ind_val(uint8_t *board, t_process *process,
							uint32_t param_val, uint32_t read_size);
void				ft_error_errno(char *msg);
void				ft_error(char *msg);
char				*get_op_name_test(uint8_t op);
int					op_uses_idx(uint8_t op);
int					op_has_type(uint8_t op);
uint32_t			get_label_size(uint8_t op);
uint32_t			get_cycles(uint8_t op);
uint32_t			get_op_size(uint8_t op, uint8_t types);
int					is_types_invalid(uint8_t op, uint8_t types);
int					valid_reg_num(uint8_t reg_num);
int					get_idx_val(int val);
void				load_programs(t_env *env, char *argv[]);
void				dump_memory(t_env *env);
void				run_game(t_env *env);
void				execute_cycle(t_env *env);
int					get_param_val(uint8_t *board, t_param param,
									t_process *process, uint8_t ind_size);
void				get_params(t_env *env, t_process *process, uint8_t op);
t_env				*create_env(uint8_t *board);
uint8_t				*create_board(void);
t_player			*create_player(uint32_t prog_num);
t_process			*create_process(int offset, uint32_t prog_num,
										char *player_name);
int					is_reg_num_invalid(uint8_t reg_num);
uint32_t			get_reg_val(t_process *process, uint8_t reg_num);
void				set_reg_val(t_process *process, uint8_t reg_num,
								uint32_t new_val);
void				inc_pc(uint32_t *regs, int inc);
void				modify_carry(t_process *process, uint32_t val);
uint32_t			get_board_val(uint8_t *board, uint32_t index,
									uint32_t size);
void				set_board_val(uint8_t *board, uint32_t index,
									uint32_t size, uint32_t val);
uint32_t			get_param_size(uint8_t type, int label_size);
void				add_process(t_env *env, t_process *process);
t_list				*kill_processes(t_env *env);
void				op_live(t_env *env, t_process *process, uint32_t pc);
void				op_load(t_env *env, t_process *process, int op);
void				op_store(t_env *env, t_process *process, uint32_t pc, uint8_t op);
void				op_arithmetic(t_env *env, t_process *process, int op);
void				op_bitwise(t_env *env, t_process *process, int op);
void				op_zjmp(t_env *env, t_process *process, uint32_t pc);
void				op_index_load(t_env *env, t_process *process, int op);
void				op_forker(t_env *env, t_process *process, uint32_t pc, int op);
void				op_aff(t_env *env, t_process *process, uint32_t pc);

void				print_instructions(void);
void				error_exit(t_env *e, int i);
t_bool add_visual(t_env *e);
t_bool add_binary(t_env *e);
t_bool add_stealth(t_env *e);
t_bool				check_duplicate_player(t_env *e, long nbr);
void				check_flag_number_valid(t_env *e, char *nbr);
t_bool				get_dump_number(t_env *e, char *nbr, int *i, int args);
t_bool				get_verbose_level(t_env *e, char *nbr, int *i, int args);
t_bool				get_cycle_number(t_env *e, char *nbr, int *i, int args);
void				reader(t_env *e, int offset, char *arg);
void				add_player_list(t_env *env, t_player *new_player);
void add_player(t_env *e, char **argv, int *i);
#endif
