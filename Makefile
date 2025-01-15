CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -O1
#  -fsanitize=thread
RM		= rm -f

NAME_MANDATORY	= philo
NAME_BONUS		= philo_bonus

########################### Mandatory ###########################

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

########################### Bonus ###########################

BONUS_DIR	= philo_bonus
BONUS_FILE	= philo.c verif_param.c philo_routine.c \
			  big_brother.c init_philo.c philo_utils.c

BONUS = $(addprefix $(BONUS_DIR)/, $(BONUS_FILE))
BONUS_OBJS	= $(BONUS:$(BONUS_DIR)%.c=$(BONUS_DIR)%.o)

NAME_BONUS := $(addprefix $(BONUS_DIR)/, $(NAME_BONUS))
INCLUDE_BONUS = -I $(addprefix $(BONUS_DIR)/, philo_bonus.h)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJS)

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE_BONUS)

.PHONY:		all clean fclean re bonus
