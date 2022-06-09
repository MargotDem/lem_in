# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 15:35:11 by mde-maul          #+#    #+#              #
#    Updated: 2022/06/09 11:00:41 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = lem-in

# SRCS = main.c handle_error.c

# OBJS = $(SRCS:.c=.o)

# FLAGS = -Wall -Werror -Wextra

# LIBS = -L ./libft -lft

# INCLUDES = -I ./

# all: $(NAME)

# $(NAME):
# 	make -C ./libft
# 	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
# 	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

# clean:
# 	make -C ./libft clean
# 	rm -f $(OBJS)

# fclean: clean
# 	make -C ./libft fclean
# 	rm -f $(NAME)

# re: fclean all

# dev:
# 	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
# 	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
# 	make clean

NAME	=	parsing

#COMPILATION
CC		=	gcc
CCFLAGS	=	-Werror -Wextra -Wall

#INCLUDE
INCL_LFT	= -I ./libft/
INCL_PARS	= -I ./includes/

#LIBRAIRIE
LIB		= -L ./libft/ -lft

#CLEAN & FCLEAN
RM_DIR	=	rm -rf
RM		=	rm	-f

#SOURCE FILES
SRC_DIR	=	./srcs/
FILES	= parsing.c

#OBJECT FILES
OBJ_DIR			=	./objectFiles/
OBJS			=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

all: $(NAME) $(LIBFT)

$(NAME): $(TEST) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $< $(LIB)
	
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL_LFT) $(INCL_PARS) -o $@ -c $<

$(LIBFT):
	@make -sC ./libft/ all
lft:
	@make -sC ./libft/ all

lft_reboot:
	@make -sC ./libft/ re

lft_clean:
	@make -sC ./libft/ clean

lft_fclean:
	@make -sC ./libft/ fclean

clean:
	@$(RM_DIR) $(OBJ_DIR)
	@echo "Object Files have been deleted"

fclean: clean
	@$(RM) $(NAME)
	@echo "Parsing file has been deleted"

re: fclean all

.PHONY: all re clean fclean
