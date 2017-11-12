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
ASM		= assembler
VM		= vm

all:	$(NAME)

$(NAME):
	@make -C $(VM)
	@make -C $(ASM)
	@cp $(VM)/corewar .
	@rsync -tr $(VM)/sound .
	@rsync -tr $(VM)/animation .
	@cp $(ASM)/asm .

clean:
	@make -C $(VM) clean
	@make -C $(ASM) clean

fclean:	clean
	@rm corewar
	@rm asm
	@make -C $(VM) fclean
	@make -C $(ASM) fclean

re:		fclean all

.PHONY:	all clean fclean re
