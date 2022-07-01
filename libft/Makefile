# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 19:52:47 by mde-maul          #+#    #+#              #
#    Updated: 2022/07/01 09:09:58 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = ft_strlen.c ft_putchar.c ft_putstr.c ft_strcmp.c \
	ft_strdup.c ft_putnbr.c ft_atoi.c ft_strcat.c ft_strncat.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c \
	ft_toupper.c ft_tolower.c ft_strncmp.c ft_strcpy.c \
	ft_strncpy.c ft_strlcat.c ft_strchr.c ft_isascii.c \
	ft_strrchr.c ft_strstr.c ft_ismatch.c ft_strnstr.c \
	ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putendl.c ft_putnbr_fd.c ft_memalloc.c \
	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	ft_strtrim.c ft_strsplit.c \
	ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_bzero.c ft_memchr.c ft_memcmp.c ft_lstnew.c \
	ft_lstadd.c ft_display_list_str.c ft_lstiter.c ft_lstmap.c \
	ft_lstdelone.c ft_lstdel.c ft_free_str_array.c \
	ft_lstadd_back.c ft_iswhitespace.c \
	ft_lstsize.c ft_abs.c btree_create_node.c btree_apply_prefix.c \
	btree_apply_infix.c btree_apply_suffix.c btree_insert_data.c \
	btree_find_node.c get_next_line.c ft_sqrt.c ft_itoa_base.c \
	ft_ull_itoa_base.c ft_ll_itoa.c ft_abs_float.c \
	ft_strjoin_replace.c ft_ll_atoi.c ft_abs_ll.c ft_isnan.c \
	ft_handle_malloc.c ft_strreplace.c

O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	@echo "Compiling ..."
	@$(CC) $(CFLAGS) -c -I ./ $(FILES) -g
	@ar rc $(NAME) $(O_FILES)
	@ranlib $(NAME)
	@echo "Libft.a created"

clean:
	@/bin/rm -f *.o
	@echo "Object files from libft has been deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(NAME) has been deleted"

re: fclean all clean

test: re
	$(CC) $(CFLAGS) test.c -L. -lft
