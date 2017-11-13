# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mda-cost <mda-cost@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:07:28 by mda-cost          #+#    #+#              #
#    Updated: 2017/11/09 17:07:29 by mda-cost         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ../asm

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

OBJS		= objs
SRCS		= srcs
INCS		= includes
LIB			= libft

INCLUDES	= -I$(INCS) -I$(LIB)
LIBS		= -L $(LIB) -lft

# headers files
I_FILES 	=	asm.h \
				op.h
I_SRCS		=	$(addprefix $(INCS)/,$(I_FILES))

# source files
C_FILES		=	asm.c \
				op.c \
				lexical.c \
				check_lexical.c \
				syntax_analyser.c \
				check_syntax.c \
				instructions.c \
				write_hex.c \
				tools.c \
				error.c \
				free.c
C_SRCS		=	$(addprefix $(SRCS)/,$(C_FILES))

# object files
O_FILES		=	$(C_FILES:.c=.o)
O_SRCS		=	$(addprefix $(OBJS)/,$(O_FILES))

# Print
ACTUAL		= $(words $(COUNT))
TOTAL		= $(words $(filter %.c,$(C_SRCS)))
INCREMENT	= $(eval COUNT+=1)

PRINTINC	= $(INCREMENT) $(PRINT)
PRINT		= printf "\r $(REDB)%3s%%$(NC)\t -->>\t$(REDB)%-60s$(NC)\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$@"
PRINTDONE	= printf "\r $(GREENB)%3s%%$(NC)\t -->>\t$(GREENB)%-60s$(NC)\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "asm"

# colors
REDB=\033[31;1m
GREENB=\033[32;1m
NC=\033[0m

all: $(NAME)

$(NAME): $(O_SRCS)
	@make -C $(LIB)
	@$(CC) $(C_FLAGS) $(LIBS) $^ -o $@ && $(PRINTDONE) && echo

$(OBJS)/%.o: $(SRCS)/%.c $(I_SRCS)
	@mkdir -p $(OBJS)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ && $(PRINTINC)

.PHONY: all clean fclean re

clean:
	@make clean -C $(LIB)
	@rm -rf $(O_FILES) $(OBJS)

fclean: clean
	@make fclean -C $(LIB)
	@rm -f $(NAME)

re: fclean all
