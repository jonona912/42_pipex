NAME = pipex
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = libft
GNL_DIR = gnl
FT_PRINTF_DIR = ft_printf

FT_PRINTF = libftprintf.a
GNL = libgnl.a
LIBFT = libft.a

LIBS = -L $(LIBFT_DIR) -lft -L $(GNL_DIR) -lgnl -L $(FT_PRINTF_DIR) -lftprintf

SRCS = arg_split_helper_1.c \
		arg_split_helper_2.c \
		arg_split.c \
		cmd_exec_1.c \
		main_pipex.c \
		ppx_free_mem.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
INCLUDES = -I include -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(FT_PRINTF_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	rm -rf $(OBJS_DIR)
	cd $(LIBFT_DIR) && $(MAKE) clean
	cd $(GNL_DIR) && $(MAKE) clean
	cd $(FT_PRINTF_DIR) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && $(MAKE) fclean
	cd $(GNL_DIR) && $(MAKE) fclean
	cd $(FT_PRINTF_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re