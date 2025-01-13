/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:31 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 15:52:13 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_param(int argc, char **argv, t_philo_info *philo_info)
{
	static pthread_mutex_t	time_mutex;
	static pthread_mutex_t	write_mutex;

	philo_info->nb_philo = ft_atol(argv[1]);
	philo_info->t_to_die = ft_atol(argv[2]);
	philo_info->t_to_eat = ft_atol(argv[3]);
	philo_info->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		philo_info->nb_must_eat = ft_atol(argv[5]);
	else
		philo_info->nb_must_eat = -1;
	if (pthread_mutex_init(&time_mutex, NULL))
		return (printf("%s\n", ERROR_INIT_MUTEX), EXIT_FAILURE);
	if (pthread_mutex_init(&write_mutex, NULL))
		return (printf("%s\n", ERROR_INIT_MUTEX), EXIT_FAILURE);
	philo_info->time_mutex = &time_mutex;
	philo_info->write_mutex = &write_mutex;
	return (EXIT_SUCCESS);
}

long	get_time(pthread_mutex_t *time_mutex)
{
	struct timeval	timeval;

	pthread_mutex_lock(time_mutex);
	gettimeofday(&timeval, NULL);
	pthread_mutex_unlock(time_mutex);
	return (timeval.tv_usec);
}

void	print_msg(t_philo_info *philo_info, short type, int self)
{
	pthread_mutex_lock(philo_info->write_mutex);

	printf("%li %i ", get_time(philo_info->time_mutex), self);
	if (type == FORK)
		printf(GREY MSG_FORK END);
	else if (type == EATING)
		printf(GREEN MSG_EATING END);
	else if (type == SLEEPING)
		printf(BLUE MSG_SLEEPING END);
	else if (type == THINKING)
		printf(WHITE MSG_THINKING END);
	else if (type == DIED)
		printf(RED MSG_DIED END);
	pthread_mutex_unlock(philo_info->write_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo			*self;

	self = (t_philo *)arg;
	while (philo_size(self) != self->info->nb_philo)
		usleep(1);
	while (1)
	{
		if (self->thread_type)
		{
			pthread_mutex_lock(&self->fork);
			print_msg(self->info, FORK, self->self_nb);
			pthread_mutex_lock(&self->next->fork);
			print_msg(self->info, FORK, self->self_nb);
		}
		else
		{
			pthread_mutex_lock(&self->next->fork);
			print_msg(self->info, FORK, self->self_nb);
			pthread_mutex_lock(&self->fork);
			print_msg(self->info, FORK, self->self_nb);
		}

		print_msg(self->info, EATING, self->self_nb);
		usleep(self->info->t_to_eat * 1000);


		pthread_mutex_unlock(&self->fork);
		pthread_mutex_unlock(&self->next->fork);
		self->last_eat = get_time(self->info->time_mutex);

		print_msg(self->info, SLEEPING, self->self_nb);
		usleep(self->info->t_to_sleep * 1000);
		print_msg(self->info, THINKING, self->self_nb);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philo;

	philo = NULL;
	if (verif_param(argc, argv))
		return (printf("%s\n", ERROR_PARAM), EXIT_FAILURE);
	if (get_param(argc, argv, &philo_info))
		return (EXIT_FAILURE);
	if (get_philo(&philo, &philo_info))
		return (EXIT_FAILURE);
	philo_free(philo);
	return (EXIT_SUCCESS);
}
