CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -O1

RM		= rm -f

NAME_MANDATORY	= philo
NAME_BONUS		= philo_bonus

MANDATORY_DIR	= philo
MANDATORY_FILE	= philo.c verif_param.c philo_utils.c       \
				  init_philo.c philo_routine.c big_brother.c

MANDATORY = $(addprefix $(MANDATORY_DIR)/, $(MANDATORY_FILE))
MANDATORY_OBJS	= $(MANDATORY:%.c=%.o)

NAME_MANDATORY := $(addprefix $(MANDATORY_DIR)/, $(NAME_MANDATORY))
INCLUDE_MANDATORY = -I $(addprefix $(MANDATORY_DIR)/, philo.h)


all: $(NAME_MANDATORY)

$(MANDATORY_DIR)/%.o: $(MANDATORY_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE_MANDATORY)

$(NAME_MANDATORY): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MANDATORY_OBJS) -lpthread

clean:
	@$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean:		clean
	@$(RM) $(NAME_MANDATORY) $(NAME_BONUS)

re:			fclean $(NAME_MANDATORY)

.PHONY:		all clean fclean re
