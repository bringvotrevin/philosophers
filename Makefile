.PHONY : bonus all clean fclean re
NAME = philo
HEADER = includes
SRCDIR = srcs/
CC = gcc
RM = rm -rf
WFLAGS = -Wall -Werror -Wextra
INCFLAGS = -I$(HEADER)
THIRDFLAGS = -lpthread
DEBUGFLAGS = -g -fsanitize=address
CFLAGS = $(WFLAGS) $(INCFLAGS) #$(DEBUGFLAGS)

SRC = main.c \
	  parsing.c \
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