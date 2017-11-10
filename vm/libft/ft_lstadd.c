/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:11:03 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/10 13:49:24 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **lst, t_list *new)
{
	if (!lst)
		;
	else if (!*lst)
		*lst = new;
	else
		new->next = *lst;
		*lst = new;
}
