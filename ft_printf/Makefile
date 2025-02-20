# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 17:51:53 by zkhojazo          #+#    #+#              #
#    Updated: 2025/01/27 22:31:58 by zkhojazo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC
LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS = ft_printf.c \
		ft_specifier.c \
		ft_print_spec.c \
		ft_put_uns_nbr.c \
		ft_put_nbr_base.c \
		ft_print_hexa.c \
		ft_putstr.c \
		ft_putnbr_ctr.c \
		ft_pos_numlen.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c ft_printf.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFTDIR)/$(LIBFTNAME) .
	mv $(LIBFTNAME) $(NAME)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f test
	cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean
	$(MAKE) all

test: main.c $(NAME)
	cc -o $@ main.c $(NAME)

t: test
	./$<

.PHONY: clean fclean re t all