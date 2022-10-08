# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 15:35:11 by mde-maul          #+#    #+#              #
#    Updated: 2022/10/05 13:54:58 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
LIBFT	=	libft.a

#COMPILATION
CC		=	gcc
CCFLAGS	=	-Werror -Wextra -Wall
#CCFLAGS	=	-Werror -Wextra -Wall -g -fsanitize=address

#INCLUDE
INCL_LFT	= -I ./libft/
INCL_PARS	= -I ./includes/
# INCL_MLX	= -I/usr/local/include

#LIBRAIRIE
LIB		= -L ./libft/ -lft
# MLX		= -L /usr/local/lib -lmlx

#CLEAN & FCLEAN
RM_DIR	=	rm -rf
RM		=	rm	-f

#SOURCE FILES
SRC_DIR	=	./srcs/

FILES = 	main.c \
			malloc_handler.c \
			free_handler.c \
			init_value.c \
			save_links.c \
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
			free_handler_solve.c \
			find_best_solution.c \
			vector_utils.c \
			handle_start_to_end_path.c \
			# viz_draw_rooms.c \
			visualizer.c \
			viz_init.c \
			viz_draw_line.c \

# FRAMEWORKS = -framework OpenGL -framework Appkit

#OBJECT FILES
OBJ_DIR			=	./objectFiles/
OBJS			=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

all: $(NAME) 

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LIB) $(MLX) $(FRAMEWORKS)
	
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL_LFT) $(INCL_PARS) $(INCL_MLX) -o $@ -c $<

$(LIBFT):
	@make -sC ./libft/ 

clean:
	@make -sC ./libft/ clean
	@$(RM_DIR) $(OBJ_DIR)
	@echo "Object Files have been deleted"
	

fclean: clean
	@make -sC ./libft/ fclean
	@$(RM) $(NAME)
	@echo "Lem-in file has been deleted"

re: fclean all

.PHONY: all re clean fclean
