/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 11:32:15 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/18 20:36:31 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

typedef struct  s_location
{
    int     line;
    int     col;
}               t_location;

typedef struct          s_token
{
    t_location          *pos;
    char                type;
    char                *value;
    struct s_token      *next;
}                       t_token;

typedef struct  s_op
{
    char        *op;
    int         pcount;
    char        ptypes[3];
    char        opcode;
    char        code_byte;
    char        label_size;
}               t_op;

typedef struct  s_label
{
    t_token *name;
    int     addr;
}               t_label;

typedef struct  s_inst
{
    int             size;
    char            opcode;
    unsigned char   type;
    int             pcount;
    t_token         *params;
    struct s_inst   *next;
}               t_inst;

typedef struct  s_env
{
    int         line;
    header_t    *header;
    t_token     *token;
    t_token     *last;
    t_label     **labels;
    t_inst      *inst;
    int         label_count;
    char        *str;
    char        *filename;
    int         pc;
}               t_env;

void		lexical_analyser(int fd, t_env *env);
void        syntax_analyser(t_env *env);
void		add_token(t_env *env, int *col, char type, char *value);
t_token		*create_token(t_env *env, int *col, char type, char *value);
void	    ft_make_inst(t_token *start, t_token *end, t_env *env);
t_op  		*get_op_by_name(char *str);
t_op        *get_op_by_opcode(int code);
int    		check_op_by_name(char *name);
void		check_quotation(t_env *env, char *line, int *col, int *quotation);
void		check_direct(t_env *env, char *line, int *col);
void		check_label(t_env *env, char *line, int *col, int j);
void		check_command(t_env *env, char *line, int *col);
void   		check_ptype(t_inst *inst, t_op *op, t_env *env);
void   		check_pcount(t_token *start, t_token *end, t_inst *inst, t_env *env);
void   		ft_write_hex(t_env *env);
void		reverse_bytes(char *str, int start, int n);
char		*ft_concat(char *s1, char *s2);
void		ft_exit(char *str);
void		ft_error(t_token *token, t_env *env, char *str);
void		syntax_error(t_token *token, t_env *env);
void		free_env(t_env *env);
