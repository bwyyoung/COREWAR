/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:06:10 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/23 16:13:49 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

void		ft_exit(char *str)
{
	ft_putendl(str);
	exit(-1);
}

void		ft_error(t_token *token, t_env *env, char *str)
{
	ft_printf("Syntax error at token [%d:%d] '%s' ",
	token->pos->line, token->pos->col, token->value);
	free_env(env);
	ft_exit(str);
}

void		syntax_error(t_token *token, t_env *env)
{
	if (token)
		ft_printf("Syntax error at token [%d:%d] '%s'",
		token->pos->line, token->pos->col, token->value);
	else
		ft_printf("Syntax error at END '(NULL)'");
	free_env(env);
	ft_exit("");
}
