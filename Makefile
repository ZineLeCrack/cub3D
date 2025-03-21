NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -I./minilibx-linux -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRCS = srcs/ft_printf/ft_printf.c srcs/ft_printf/ft_putchar.c srcs/ft_printf/ft_putstr.c srcs/ft_printf/ft_putnbr.c srcs/ft_printf/ft_putnbr_unsigned.c \
	   srcs/ft_printf/ft_puthex.c srcs/ft_printf/ft_puthexa.c srcs/libft/ft_atoi.c srcs/libft/ft_bzero.c srcs/libft/ft_calloc.c srcs/libft/ft_isalnum.c \
	   srcs/libft/ft_isalpha.c srcs/libft/ft_isascii.c srcs/libft/ft_isdigit.c srcs/libft/ft_isprint.c srcs/libft/ft_itoa.c srcs/libft/ft_memchr.c \
	   srcs/libft/ft_memcmp.c srcs/libft/ft_memcpy.c srcs/libft/ft_memmove.c srcs/libft/ft_memset.c srcs/libft/ft_putchar_fd.c srcs/libft/ft_putendl_fd.c \
	   srcs/libft/ft_putnbr_fd.c srcs/libft/ft_putstr_fd.c srcs/libft/ft_split.c srcs/libft/ft_strchr.c srcs/libft/ft_strdup.c srcs/libft/ft_striteri.c\
	   srcs/libft/ft_strjoin.c srcs/libft/ft_strlcat.c srcs/libft/ft_strlcpy.c srcs/libft/ft_strlen.c srcs/libft/ft_strmapi.c srcs/libft/ft_strncmp.c \
	   srcs/libft/ft_strnstr.c srcs/libft/ft_strrchr.c srcs/libft/ft_strtrim.c srcs/libft/ft_substr.c srcs/libft/ft_tolower.c srcs/libft/ft_toupper.c \
	   srcs/libft/ft_lstnew_bonus.c srcs/libft/ft_lstadd_front_bonus.c srcs/libft/ft_lstsize_bonus.c srcs/libft/ft_lstlast_bonus.c \
	   srcs/libft/ft_lstadd_back_bonus.c srcs/libft/ft_lstdelone_bonus.c srcs/libft/ft_lstclear_bonus.c srcs/libft/ft_lstiter_bonus.c srcs/libft/ft_lstmap_bonus.c \
	   srcs/get_next_line/get_next_line_utils.c srcs/get_next_line/get_next_line.c \
	   srcs/init.c srcs/key_press.c srcs/minimap.c srcs/raycasting.c srcs/raycasting_utils.c srcs/utils.c srcs/utils2.c srcs/free.c srcs/main.c \
	   srcs/parsing/parsing.c srcs/parsing/map_parsing.c srcs/parsing/map_flood_fill.c srcs/parsing/map_player.c \
	   srcs/parsing/scene_parsing.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

minilibx-linux/libmlx.a:
	@$(MAKE) -C minilibx-linux 

$(NAME): minilibx-linux/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re