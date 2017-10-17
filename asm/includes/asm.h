/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 11:32:15 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/17 12:42:37 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
