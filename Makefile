.PHONY : bonus all clean fclean re
NAME = philo
SRCDIR = srcs/
HEADER = includes
RM = rm -rf
CC = gcc
INCFLAGS = -I$(HEADER)
WFLAGS = -Wall -Werror -Wextra
THIRDFLAGS = -lpthread
DEBUGFLAGS = -g -fsanitize=address

CFLAGS = $(WFLAGS) $(INCFLAGS) #$(DEBUGFLAGS)

SRC = main.c \
	  parsing.c \
	  create_thread.c \
	  make_philo_fork.c \
	  sleep_think.c \
	  check.c \
	  util.c

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(THRIDFLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all