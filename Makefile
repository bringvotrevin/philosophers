.PHONY : bonus all clean fclean re
NAME = philo
HEADER = includes
SRCDIR = srcs/
CC = gcc
RM = rm -rf
WFLAGS = -Wall -Werror -Wextra
INCFLAGS = -I$(HEADER)
DEBUGFLAGS = -g -fsanitize=address
CFLAGS = $(WFLAGS) $(INCFLAGS) #$(DEBUGFLAGS)

SRC = main.c \
		parsing.c

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(SRCS:.c=.o)

${NAME} :	${OBJS}
			$(CC) $(CFLAGS) $(OBJS) $(SRCS) -o $(NAME)

all : ${NAME}

clean :
			$(RM) $(OBJS)

fclean :	clean
			$(RM) $(NAME)

re :	fclean all