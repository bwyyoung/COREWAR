/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:09:04 by douglas           #+#    #+#             */
/*   Updated: 2017/07/13 14:33:37 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_node(t_list *node)
{
	SAFE_DELETE(node->content);
	SAFE_DELETE(node);
}

void		ft_free_list(t_list *start)
{
	ft_lstiter(start, free_node);
}
