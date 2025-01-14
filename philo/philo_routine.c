/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:18:52 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/14 09:59:05 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philo_info *info)
{
	pthread_mutex_lock(&info->dead_mutex);
	if (info->is_dead)
		return (pthread_mutex_unlock(&info->dead_mutex), true);
	pthread_mutex_unlock(&info->dead_mutex);
	return (false);
}


bool	philo_type_1(t_philo *self)
{
	pthread_mutex_lock(&self->fork);
	if (print_msg(self->info, FORK, self->self_nb))
		return (pthread_mutex_unlock(&self->fork), EXIT_FAILURE);
	pthread_mutex_lock(&self->next->fork);
	if (print_msg(self->info, FORK, self->self_nb))
		return (pthread_mutex_unlock(&self->fork),
			pthread_mutex_unlock(&self->next->fork), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	philo_type_2(t_philo *self)
{
	pthread_mutex_lock(&self->next->fork);
	if (print_msg(self->info, FORK, self->self_nb))
		return (pthread_mutex_unlock(&self->next->fork), EXIT_FAILURE);
	pthread_mutex_lock(&self->fork);
	if (print_msg(self->info, FORK, self->self_nb))
		return (pthread_mutex_unlock(&self->fork),
			pthread_mutex_unlock(&self->next->fork), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	philo_eat(t_philo *self)
{
	if (self->thread_type)
	{
		if (philo_type_1(self))
			return (EXIT_FAILURE);
	}
	else
	{
		if (philo_type_2(self))
			return (EXIT_FAILURE);
	}
	print_msg(self->info, EATING, self->self_nb);
	if (print_msg(self->info, FORK, self->self_nb))
		return (EXIT_FAILURE);
	usleep(self->info->t_to_eat * 1000);
	if (print_msg(self->info, FORK, self->self_nb))
		return (EXIT_FAILURE);
	pthread_mutex_unlock(&self->fork);
	pthread_mutex_unlock(&self->next->fork);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	while (1)
	{
		if (philo_eat(self))
			return (NULL);
		pthread_mutex_lock(&self->last_meat_mutex);
		self->last_meat = get_time(&self->info->time_mutex);
		pthread_mutex_unlock(&self->last_meat_mutex);
		if (is_philo_dead(self->info))
			return (NULL);
		print_msg(self->info, SLEEPING, self->self_nb);
		usleep(self->info->t_to_sleep * 1000);
		if (is_philo_dead(self->info))
			return (NULL);
		print_msg(self->info, THINKING, self->self_nb);
	}
	return (NULL);
}
