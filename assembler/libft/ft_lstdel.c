/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:06:51 by ppatel            #+#    #+#             */
/*   Updated: 2016/11/25 15:58:17 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cur;
	t_list	*next;

	cur = *alst;
	while (cur)
	{
		next = cur->next;
		del(cur->content, cur->content_size);
		free(cur);
		cur = next;
	}
	*alst = NULL;
}
