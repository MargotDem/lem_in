# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briffard <briffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 08:21:48 by briffard          #+#    #+#              #
#    Updated: 2022/06/01 09:50:43 by briffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

#COMPILATION
CC		=	gcc
CCFLAGS	=	-Werror -Wextra -Wall

#INCLUDE
INCL	= -I ./includes

#CLEAN & FCLEAN
RM_DIR	=	rm -rf
RM		=	rm	-f

#SOURCE FILES
SRC_DIR	=	./libft/
FILES	=ft_putchar.c	ft_putchar_fd.c		ft_putendl.c		ft_tolower.c\
	ft_putendl_fd.c		ft_putnbr.c			ft_putnbr_fd.c		ft_toupper.c\
	ft_putstr.c			ft_putstr_fd.c		ft_strlen.c			ft_atoi.c	\
	ft_isalpha.c		ft_itoa.c			ft_strjoin.c		ft_bzero.c	\
	ft_isalnum.c		ft_isascii.c		ft_isdigit.c		ft_isprint.c\
	ft_memccpy.c		ft_strnew.c			ft_memcpy.c			ft_memset.c	\
	ft_strcat.c			ft_strchr.c			ft_strcmp.c			ft_strcpy.c	\
	ft_strdup.c			ft_strlcat.c		ft_strncat.c		ft_strncmp.c\
	ft_strncpy.c		ft_strnstr.c		ft_strrchr.c		ft_strstr.c	\
	ft_strequ.c			ft_strnequ.c		ft_strtrim.c		ft_isspace.c\
	ft_strclr.c			ft_strdel.c			ft_strsub.c			ft_striter.c\
	ft_striteri.c		ft_memalloc.c		ft_memchr.c			ft_memcmp.c	\
	ft_memdel.c			ft_memmove.c		ft_strmapi.c		ft_strmap.c	\
	ft_strsplit.c		ft_cleanstr.c		ft_lstnew.c			ft_lstadd.c	\
	ft_lstdelone.c		ft_lstdel.c			ft_color.c	\
	ft_putstrcolor.c	ft_putcharcolor.c	ft_printbits.c\
	ft_numlength.c		ft_randomnbr.c 		ft_display_file.c	\
	ft_get_next_line.c		ft_swap.c		ft_abs_float.c		ft_isupper.c\
	ft_u_itoa.c 		ft_ll_itoa.c		ft_l_itoa.c		ft_u_short_itoa.c\
	ft_abs_int.c 		ft_uitoa_base.c 	ft_reversestr.c \
	ft_charjoin.c 		ft_strtoupper.c		ft_strtoupper.c  \
	ft_isdoubleneg.c	ft_isintneg.c 		ft_strjoin_replace.c\

#FT_PRINTF FILES
FTPRINTF_DIR 	=	./ft_printf/
FT_PRINTF_SRC 	=	ft_printf.c												\
					struct_init.c											\
					handle_Flag.c error.c									\
	conv_str.c  conv_int.c conv_uint.c conv_p.c conv_dbl.c 	\
	conv_void.c												\
	print_str.c	print_int.c									\
	handle_sizePrefix_for_flag_d.c							\
	utils_funct.c utils_print_int.c utils_print_int2.c 		\
	ft_str_rounding.c 										\
	bonus.c 												\

#OBJECT FILES
OBJ_DIR			=	./objectFiles/
LFT_OBJS		=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))
FTPRINTF_OBJS	=	$(addprefix $(OBJ_DIR), $(FT_PRINTF_SRC:%.c=%.o))


all: $(NAME)

$(NAME): $(LFT_OBJS) $(FTPRINTF_OBJS)
	@echo "Creation of libftprintf"
	@ar rcs $(NAME) $(LFT_OBJS) $(FTPRINTF_OBJS)
	@echo "Libftprintf created."
	@ranlib $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL) -o $@ -c $<

$(OBJ_DIR)%.o:$(FTPRINTF_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CCFLAGS) $(INCL) -o $@ -c $<

clean:
	@$(RM_DIR) $(OBJ_DIR)
	@echo "Object Files directory has been deleted"

fclean: clean
	@$(RM) $(NAME)
	@echo "libftprintf.a file has been deleted"

re: fclean all

.PHONY: all re clean fclean