# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 15:22:24 by bhugo             #+#    #+#              #
#    Updated: 2019/11/19 22:08:01 by bcd hugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	libftprintf.a
LIBFT_A =	libft.a

SRCS = 	ft_printf.c\
		ft_itoa_base.c\
		ft_atoi_parser.c\
		ft_strndup.c\
		ft_long_itoa.c\
		format_percent.c\
		format_upper_hex.c\
		format_hex.c\
		format_unsigned_int.c \
		format_oct.c \
		format_int.c\
		format_pointer.c\
		format_char.c\
		format_str.c\
		format_float.c\
		ft_write_buffer.c\
		ft_putchar_buffer.c\
		ft_putstr_buffer.c\


OBJS = 	ft_printf.o \
		ft_itoa_base.o \
		ft_atoi_parser.o\
		ft_strndup.o\
		ft_long_itoa.o\
		format_percent.o\
		format_upper_hex.o\
		format_hex.o\
		format_unsigned_int.o\
		format_oct.o \
		format_int.o\
		format_pointer.o\
		format_char.o\
		format_str.o\
		format_float.o\
		ft_write_buffer.o\
		ft_putchar_buffer.o\
		ft_putstr_buffer.o\

FLAGS = -Wall -Wextra -Werror

LIB = make -C libft/

HEADER = ft_printf.h

LIB_DIR = ./libft/

all: $(NAME)

$(NAME):
	$(LIB)
	@make -C $(LIB_DIR)
	@cp $(LIB_DIR)$(LIBFT_A) .
	@mv $(LIBFT_A) $(NAME)
	gcc -c $(FLAGS) $(SRCS) -I $(HEADER) -I $(LIB_DIR) 
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	make clean -C $(LIB_DIR)

fclean:
	rm -f $(NAME)
	rm -f $(OBJS)
	make fclean -C $(LIB_DIR)

re: fclean all
