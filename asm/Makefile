# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/17 14:59:23 by ppatel            #+#    #+#              #
#    Updated: 2017/10/17 16:46:22 by ppatel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall \
		-Wextra \
		-Werror \

NAME = asm

SDIR = srcs

ODIR = objects

SRCS = $(SDIR)/asm.c \
	#    $(SDIR)/free_all.c \

OBJ = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)

HDRS = -I./includes \
	   -I./libft/includes

LIBFT = ./libft/libft.a

LIBS = -L./libft/ -lft

all : $(NAME)

$(NAME): $(ODIR) $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(LIBS) $(OBJ) -o $@
	@echo "asm created."

$(ODIR):
	@mkdir objects

$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(FLAGS) -c $< $(HDRS) -o $@
	@echo "Object created."

$(LIBFT):
	@make -C libft/

clean:
	@rm -rf $(ODIR)
	@make clean -C libft
	@echo "Objects deleted."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "Executable deleted."

re: fclean all

.PHONY: all clean fclean re
