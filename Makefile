NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS_DIR = srcs
SRCS_BONUS_DIR = srcs_bonus
OBJS_DIR = objs
OBJS_BONUS_DIR = objs_bonus
LIBFT_DIR = libft
GNL_DIR = gnl
FT_PRINTF_DIR = ft_printf

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
GNL = $(GNL_DIR)/libgnl.a
LIBFT = $(LIBFT_DIR)/libft.a

LIBS = -L $(LIBFT_DIR) -lft -L $(GNL_DIR) -lgnl -L $(FT_PRINTF_DIR) -lftprintf

SRCS = arg_split_helper_1.c \
		arg_split_helper_2.c \
		arg_split.c \
		cmd_exec_1.c \
		cmd_exec_2.c \
		main_pipex.c \
		ppx_errors.c \
		ppx_free_mem.c

SRCS_BONUS = arg_split_helper_1_bonus.c \
			arg_split_helper_2_bonus.c \
			arg_split_bonus.c \
			cmd_exec_1_bonus.c \
			cmd_exec_2_bonus.c \
			main_pipex_bonus.c \
			ppx_errors_bonus.c \
			ppx_free_mem_bonus.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR)/, $(SRCS_BONUS:.c=.o))
INCLUDES = -I include -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(FT_PRINTF_DIR)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(GNL) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
	@mkdir -p $(OBJS_BONUS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(OBJS_BONUS_DIR)
	cd $(LIBFT_DIR) && $(MAKE) clean
	cd $(GNL_DIR) && $(MAKE) clean
	cd $(FT_PRINTF_DIR) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	cd $(LIBFT_DIR) && $(MAKE) fclean
	cd $(GNL_DIR) && $(MAKE) fclean
	cd $(FT_PRINTF_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re