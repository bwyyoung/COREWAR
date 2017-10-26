/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:37:30 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/26 18:36:29 by dengstra         ###   ########.fr       */
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
	stealth,
	debug
}					e_options;

typedef struct			s_player
{
	int					lives;
	char				*name;
	uint32_t			prog_num;
	int					file_pos;
	struct s_player		*prev;
	struct s_player		*next;
}						t_player;

typedef struct			s_process
{
	uint32_t			types;
	uint32_t			regs[REG_NUMBER + 1];	// should be REG_SIZE datatype
	uint8_t				param_type[3];
	uint32_t			param_val[3];
	int					carry;
	int					cycles_left;
	char				*name;
	uint32_t			prog_num;
	int					lives;
	int					op;
	uint32_t			process_num;
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

typedef struct			s_env
{
	int					cycle_to_die;
	int					cycles_since_check;
	long				total_cycles;
	int					lives_since_check;
	uint32_t			num_processes;
	uint8_t				*board;
	//t_list				*processes;
	//t_list				*players;
	t_list				*element;
	t_player			*lst_players;
	t_process			*lst_process;
	int					last_live_num;
	char				*last_live_name;
	int					checks;
	int					options[6];
	int					num_players;
	int					to_die;
	long				dump_value;
	long				cycle_value;
	long				verbose_value;
	t_player			*new_player;
	t_process			*new_process;
	t_process			*new_fork;
	uint32_t			prog_num;
	uint32_t			offset;
	int					i;
	int					j;
	int					k;
	int					x;
	int					y;
	int					z;
	int					program_size;
}						t_env;

typedef struct			s_index_info
{
	int					index1;
	int					index2;
	int					index_sum;
}						t_index_info;

void					print_verbosity_sixteen(t_env *env, t_process *process, int inc);
t_index_info			*create_index_info(int index1, int index2, int index_sum);
int						check_param_reg_nums(t_process *process, int p0, int p1, int p2);
void					print_verbosity_four_vals(t_process *process);
uint32_t				get_ind_val(uint8_t *board, t_process *process,
								uint32_t param_val, uint32_t read_size);
void					ft_error_errno(char *msg);
void					ft_error(char *msg);
char					*get_op_name(int op);
int						op_uses_idx(int op);
int						op_has_type(int op);
uint32_t				get_label_size(int op);
uint32_t				get_cycles(int op);
int						get_num_params(int op);
uint32_t				get_op_size(t_process *process);
int						is_types_invalid(int op, uint8_t types);
int						valid_reg_num(uint32_t reg_num);
int						get_idx_val(int val);
void					load_programs(t_env *env, char *argv[]);
void					dump_memory(t_env *env);
void					run_game(t_env *env);
void					execute_cycle(t_env *env);
uint32_t				get_param_val(uint8_t *board, int which_param,
						t_process *process, uint8_t ind_size);
void					get_params(t_env *env, t_process *process, int op);
t_env					*create_env(uint8_t *board);
uint8_t					*create_board(void);
t_player				*create_player(uint32_t prog_num);
t_process				*create_process(t_env *e);
int						is_reg_num_invalid(uint32_t reg_num);
uint32_t				get_reg_val(t_process *process, uint32_t reg_num);
void					set_reg_val(t_process *process, uint32_t reg_num,
						uint32_t new_val);
void					inc_pc(t_process *process, int inc);
void					modify_carry(t_process *process, uint32_t val);
uint32_t				get_board_val(uint8_t *board, uint32_t index,
						uint32_t size);
void					set_board_val(uint8_t *board, uint32_t index,
						uint32_t size, uint32_t val);
uint32_t				get_param_size(uint8_t type, int label_size);
//void					add_process(t_env *env, t_process *process);
void					kill_processes(t_env *env);
void					op_live(t_env *env, t_process *process);
void					op_load(t_env *env, t_process *process);
void					op_store(t_env *env, t_process *process, uint32_t pc, int op);
void					op_arithmetic(t_env *env, t_process *process, int op);
void					op_bitwise(t_env *env, t_process *process, int op);
void					op_zjmp(t_env *env, t_process *process);
void					op_index_load(t_env *env, t_process *process, int op);
void					op_forker(t_env *env, t_process *process, int op);
void					op_aff(t_env *env, t_process *process, uint32_t pc);

void					print_instructions(void);
void					error_exit(t_env *e, int i);
t_bool					add_visual(t_env *e);
t_bool					add_binary(t_env *e);
t_bool					add_stealth(t_env *e);
t_bool					check_duplicate_player(t_env *e, long nbr);
void					check_flag_number_valid(t_env *e, char *nbr);
t_bool					get_dump_number(t_env *e, char *nbr, int *i, int args);
t_bool					get_verbose_level(t_env *e, char *nbr, int *i, int args);
t_bool					get_cycle_number(t_env *e, char *nbr, int *i, int args);
void					reader(t_env *e, int offset, char *arg);
//void					add_player_list(t_env *env, t_player *new_player);
void					add_player(t_env *e, char **argv, int *i);
void					delete_env(t_env *env);
t_player				*lst_players_add(t_env *e, t_player *p);
void					lst_players_del(t_env *e, t_player *p);
void					lst_process_add(t_env *e, t_process *p);
void					lst_process_del(t_env *e, t_process *p);
void					lst_process_clr(t_env *e);
void					lst_players_clr(t_env *e);

int						lst_process_len(t_process *lst);
int						lst_players_len(t_player *lst);
#endif
