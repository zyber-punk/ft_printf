# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 16:52:06 by uzyberaj          #+#    #+#              #
#    Updated: 2024/12/30 20:44:05 by uzyberaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
SRCS = main/ft_printf.c main/buffer.c main/format_utils.c main/parser.c \
		main/render_char.c main/render_int.c main/utils.c

BONUSSRCS = bonus/ft_printf_bonus.c bonus/buffer_bonus.c bonus/format_utils_bonus.c \
		bonus/parser_bonus.c bonus/render_char_bonus.c bonus/render_int_bonus.c \
		bonus/utils_bonus.c

OBJ = $(SRCS:.c=.o)
BONUSOBJ = $(BONUSSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus: $(BONUSOBJ)
	ar -rcs $(NAME) $(BONUSOBJ)

clean:
	rm -f $(OBJ) $(BONUSOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all