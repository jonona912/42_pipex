NAME = pipex
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = libft

LIBFT = libft.a

LIBS = -L $(LIBFT_DIR) -lft

SRCS = main_pipex.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
INCLUDES = -I include -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	cd $(LIBFT_DIR) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re