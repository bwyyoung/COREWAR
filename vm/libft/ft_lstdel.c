/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:11:08 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/24 11:07:50 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		**mlist;
	t_list		*thenext;

	if (alst == NULL)
		return ;
	else if (*alst == NULL)
		return ;
	mlist = alst;
	while ((*mlist)->next != NULL)
	{
		thenext = (*mlist)->next;
		ft_lstdelone(mlist, del);
		*mlist = NULL;
		*mlist = thenext;
	}
	ft_lstdelone(mlist, del);
	mlist = NULL;
	*alst = NULL;
}

