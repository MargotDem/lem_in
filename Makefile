# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 15:35:11 by mde-maul          #+#    #+#              #
#    Updated: 2022/08/02 09:02:22 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in

#COMPILATION
CC		=	gcc
CCFLAGS	=	-Werror -Wextra -Wall

#INCLUDE
INCL_LFT	= -I ./libft/
INCL_PARS	= -I ./includes/
INCL_MLX	= -I/usr/local/include

#LIBRAIRIE
LIB		= -L ./libft/ -lft
MLX		= -L /usr/local/lib -lmlx

#CLEAN & FCLEAN
RM_DIR	=	rm -rf
RM		=	rm	-f

#SOURCE FILES
SRC_DIR	=	./srcs/

FILES = 	main.c \
			malloc_handler.c \
			free_handler.c \
			init_value.c \
			panic.c \
			mapreader.c mapreader_tools.c\
			get_ants.c \
			parsing_tools.c \
			exit_parsing.c \
			save_data.c save_data_tools.c \
			hashtable_main.c hashtable_malloc.c\
			print_man.c \
			add_node_to_be_visited.c \
			display_result.c \
			get_aug_paths.c \
			get_paths.c \
			handle_error.c \
			history_utils.c \
			list_utils.c \
			paths_utils.c \
			solve.c \
			utils.c \
			visualizer.c \
			free_handler_solve.c \
			find_best_solution.c \
			vector_utils.c \

FRAMEWORKS = -framework OpenGL -framework Appkit

#OBJECT FILES
OBJ_DIR			=	./objectFiles/
OBJS			=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

all: $(NAME) $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LIB) $(MLX) $(FRAMEWORKS)
	
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL_LFT) $(INCL_PARS) $(INCL_MLX) -o $@ -c $<

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
