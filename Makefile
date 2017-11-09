# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mda-cost <mda-cost@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 18:51:43 by mda-cost          #+#    #+#              #
#    Updated: 2017/11/09 18:51:44 by mda-cost         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= corewar
ASM		= asm
VM		= vm

all:	$(NAME)

$(NAME):
	@make -C $(VM)
	@make -C $(ASM)

clean:
	@make -C $(VM) clean
	@make -C $(ASM) clean

fclean:	clean
	@make -C $(VM) fclean
	@make -C $(ASM) fclean

re:		fclean all

.PHONY:	all clean fclean re