CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilpthread
RM	= rm -f

NAME = philo_bonus

SRCS = main.c init.c utils.c eat_sleep_think.c go_philosophers.c

HEADER	=	philosophers.h

OBJS = ${SRCS:.c=.o}

all:		${NAME}

.c.o: ${SRCS}

			@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS) $(HEADER)
			@$(CC) $(OBJS) -o $(NAME)
		
clean:		
			@${RM} $(OBJS)
	
fclean:		clean
			@$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re