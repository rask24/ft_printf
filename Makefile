NAME = libftprintf.a
INC_DIR = includes
SRC_DIR = srcs
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT_NAME = libft.a
SRCS = $(SRC_DIR)/ft_printf.c \
		$(SRC_DIR)/parse_spec.c \
		$(SRC_DIR)/conversion_router.c \
		$(SRC_DIR)/print_string.c \
		$(SRC_DIR)/print_integer.c \
		$(SRC_DIR)/nbr_utils.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)
ARFLAGS = cr

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT_NAME) $(LIBFT_NAME)
	mv $(LIBFT_NAME) $@
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

bonus: all

test: main.c $(NAME)
	$(CC) main.c $(NAME) -I $(INC_DIR)
	./a.out | cat -e 

.PHONY: all clean fclean re bonus
