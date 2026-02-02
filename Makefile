SRC_DIR    = src
LIBFT_DIR  = libft

SRCS    = main.c ar_parser.c elf_parser.c format_utils.c display.c elf_handler.c
OBJS    = $(SRCS:%.c=$(SRC_DIR)/%.o)

NAME    = ft_nm
LIBFT   = $(LIBFT_DIR)/libft.a

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)


$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
