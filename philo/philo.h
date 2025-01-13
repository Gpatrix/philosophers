/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:54 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 15:46:41 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>

#define ERROR_PARAM \
"./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

#define ERROR_CREATE_PHILO_STRUCT "error creating philo struct"
#define ERROR_CREATE_PHILO "error creating philo"
#define ERROR_INIT_MUTEX "error init mutex"
#define ERROR_INIT_JOIN "error pthread_join"

#define END   "\033[0m"
#define GREY  "\033[1;30m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE  "\033[1;36m"
#define WHITE "\033[1;37m"


#define FORK 1
#define EATING 2
#define SLEEPING 3
#define THINKING 4
#define DIED 5

#define MSG_FORK "has taken a fork\n"
#define MSG_EATING "is eating\n"
#define MSG_SLEEPING "is sleeping\n"
#define MSG_THINKING "is thinking\n"
#define MSG_DIED "died\n"

typedef struct s_philo_info
{
	int				nb_philo;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			nb_must_eat;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*time_mutex;
}		t_philo_info;

typedef struct s_philo
{
	pthread_t			philo;
	int					self_nb;
	long				last_eat;
	bool				thread_type;
	pthread_mutex_t		fork;
	t_philo_info		*info;
	struct s_philo		*next;
}		t_philo;

bool	verif_param(int argc, char **argv);
long	ft_atol(const char *nptr);

bool	get_philo(t_philo **philo, t_philo_info *philo_info);

void	*philo_routine(void *arg);

t_philo	*philo_new(t_philo_info *philo_info, int self_nb, bool thread_type);
bool	philo_add_last(t_philo	**lst, t_philo	*philo);
void	philo_free(t_philo *lst);

int		philo_size(t_philo *lst);
