# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 15:53:24 by mde-maul          #+#    #+#              #
#    Updated: 2022/06/01 15:53:25 by mde-maul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = main.c handle_error.c graph_array.c graph_functions.c \
	history_functions.c make_graph.c display_result.c \
	list_functions.c paths_functions1.c paths_functions2.c \
	helpers.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBS = -L ./libft -lft

INCLUDES = -I ./libft/includes/

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

dev:
	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
	make clean
