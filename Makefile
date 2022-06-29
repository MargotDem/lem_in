# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 15:35:11 by mde-maul          #+#    #+#              #
#    Updated: 2022/06/29 10:06:25 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
FILES	= 	parsing_main.c parsing_ants.c parsing_rooms.c parsing_utils.c \
			parsing_utils2.c parsing_error.c parsing_utils_list.c \
			parsing_command.c parsing_connexion.c parsing_mem_handling.c \
			parsing_connexion_handling.c \
			hashtable_main.c \
			#parsing_tree \
		

#OBJECT FILES
OBJ_DIR			=	./objectFiles/
OBJS			=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

all: $(NAME) $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LIB) -g
	
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL_LFT) $(INCL_PARS) -o $@ -c $< -g

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
