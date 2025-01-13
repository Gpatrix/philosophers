/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:31 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 12:50:03 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_param(int argc, char **argv, t_philo_info *philo_info)
{
	philo_info->nb_philo = ft_atol(argv[1]);
	philo_info->t_to_die = ft_atol(argv[2]);
	philo_info->t_to_eat = ft_atol(argv[3]);
	philo_info->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		philo_info->nb_must_eat = ft_atol(argv[5]);
	else
		philo_info->nb_must_eat = -1;
}

long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_usec * 1000);
}

void	print_msg(pthread_mutex_t *write_mutex, short type, int self)
{
	pthread_mutex_lock(write_mutex);
	printf("%li %i ", get_time(), self);
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
	pthread_mutex_unlock(write_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo			*self;

	self = (t_philo *)arg;
	while (1)
	{
		print_msg(self->write_mutex, THINKING, self->self_nb);
		pthread_mutex_lock(&self->fork);
		print_msg(self->write_mutex, FORK, self->self_nb);
		pthread_mutex_lock(&self->next->fork);
		print_msg(self->write_mutex, FORK, self->self_nb);

		print_msg(self->write_mutex, EATING, self->self_nb);
		usleep(self->philo_info->t_to_eat);

		pthread_mutex_unlock(&self->fork);
		pthread_mutex_unlock(&self->next->fork);

		print_msg(self->write_mutex, SLEEPING, self->self_nb);
		usleep(self->philo_info->t_to_sleep);
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
	get_param(argc, argv, &philo_info);
	get_philo(&philo, &philo_info);
	philo_free(philo);
	return (EXIT_SUCCESS);
}
