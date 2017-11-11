/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:07:20 by ppatel            #+#    #+#             */
/*   Updated: 2017/11/11 21:17:29 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

void		init_label(t_env *env, t_token *token)
{
	int			count;

	count = 0;
	while (token)
	{
		if (token->type == T_LAB)
			count++;
		token = token->next;
	}
	if (!(env->labels = (t_label **)malloc(sizeof(t_label) * count)))
		return ;
}

t_token		*syntax_header(t_token *token, t_env *env)
{
	if (!token || ft_strcmp(token->value, NAME_CMD_STRING))
		syntax_error(token, env);
	if (!token->next || token->next->type != 32 ||
		token->pos->line != token->next->pos->line)
		syntax_error(token->next, env);
	token = token->next;
	if (!token->next || ft_strcmp(token->next->value, COMMENT_CMD_STRING) ||
		token->pos->line == token->next->pos->line)
		syntax_error(token->next, env);
	token = token->next;
	if (!token->next || token->next->type != 32 ||
		token->pos->line != token->next->pos->line)
		syntax_error(token->next, env);
	token = token->next;
	if (!token->next || token->next->pos->line == token->pos->line)
		syntax_error(token->next, env);
	return (token->next);
}

t_token		*syntax_instruction(t_token *token, t_env *env)
{
	int		line;

	token = token->type == T_LAB ? token->next : token;
	if (!token || (token && token->type == T_LAB))
		return (token);
	if (!token || token->type != 16)
		syntax_error(token, env);
	line = token->pos->line;
	token = token->next;
	if (!token || (token->type != T_REG && token->type != T_DIR
		&& token->type != T_IND))
		syntax_error(token, env);
	token = token->next;
	while (token && token->pos->line == line)
	{
		if (!token || token->value[0] != SEPARATOR_CHAR ||
			!token->next || token->next->pos->line != line)
			syntax_error(token, env);
		token = token->next;
		if (!token || (token->type != T_REG && token->type != T_DIR &&
			token->type != T_IND))
			syntax_error(token, env);
		token = token->next;
	}
	return (token);
}

void		syntax_analyser(t_env *env)
{
	t_token		*token;
	t_token		*end;

	token = env->token;
	token = syntax_header(token, env);
	init_label(env, token);
	while (token)
	{
		if (token->type == T_LAB && token->next && token->next->type == T_LAB)
			if (token->pos->line == token->next->pos->line)
				syntax_error(token->next, env);
		end = syntax_instruction(token, env);
		ft_make_inst(token, end, env);
		token = end;
	}
}
