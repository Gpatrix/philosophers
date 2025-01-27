CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -O1

RM		= rm -f

NAME	= philo

FILE	= philo.c verif_param.c philo_utils.c   big_brother.c  \
				  init_philo.c  philo_routine.c 

OBJS	= $(FILE:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
	@$(RM) $(NAME) $(NAME_BONUS)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
