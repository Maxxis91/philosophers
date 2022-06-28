CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilpthread
RM	= rm -f

NAME = philo

SRCS = main.c initialization.c utils.c routine.c threads_and_lock.c who_died.c

DEPS	=	philosophers.h

OBJS = ${SRCS:.c=.o}

all:		${NAME}

.c.o: ${SRCS}

			@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS) $(DEPS)
			@$(CC) $(OBJS) -o $(NAME)
		
clean:		
			@${RM} $(OBJS)
	
fclean:		clean
			@$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re