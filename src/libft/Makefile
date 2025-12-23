NAME = libft.a

INCDIR = .

SRCS = ft_atoi.c ft_isalpha.c ft_itoa.c ft_memcpy.c ft_putendl_fd.c \
		ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c ft_bzero.c \
		ft_isascii.c ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_calloc.c ft_isdigit.c ft_memchr.c \
		ft_memset.c ft_putstr_fd.c ft_striteri.c ft_strlen.c ft_strrchr.c \
		ft_toupper.c ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c \
		ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_tabjoin.c

SRCS_BONUS = ft_lstlast.c ft_lstdelone.c ft_lstnew.c ft_lstadd_front.c \
				ft_lstiter.c ft_lstclear.c ft_lstmap.c ft_lstadd_back.c \
				ft_lstsize.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCDIR)
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o$@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re
