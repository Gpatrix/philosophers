/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:18:52 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 17:43:55 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo_info *philo_info, short type, int self)
{
	pthread_mutex_lock(philo_info->write_mutex);

	printf("%li %i ",
		get_time(philo_info->time_mutex) - philo_info->start_time,
		self);
	if (type == FORK)
		printf(GREY MSG_FORK END);
	else if (type == EATING)
		printf(GREEN MSG_EATING END);
	else if (type == SLEEPING)
		printf(BLUE MSG_SLEEPING END);
	else if (type == THINKING)
		printf(WHITE MSG_THINKING END);
	pthread_mutex_unlock(philo_info->write_mutex);
}

void	get_fork(t_philo *self)
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
}

void	*philo_routine(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	while (philo_size(self) != self->info->nb_philo)
		usleep(1);
	self->last_eat = get_time(self->info->time_mutex);
	while (1)
	{
		get_fork(self);
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
