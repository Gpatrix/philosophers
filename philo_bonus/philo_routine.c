/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:18:52 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/14 17:49:43 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_end(t_philo_info *info)
{
	pthread_mutex_lock(&info->end_mutex);
	if (info->is_ended == true)
		return (pthread_mutex_unlock(&info->end_mutex), true);
	else
		return (pthread_mutex_unlock(&info->end_mutex), false);
}

bool	update_meal(t_philo *self)
{
	pthread_mutex_lock(&self->meal_mutex);
	self->last_meal = get_time(self->info);
	self->nb_meal++;
	pthread_mutex_unlock(&self->meal_mutex);
	if (self->last_meal == -1 || verif_meal(self))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	philo_eat(t_philo *self)
{
	pthread_mutex_lock(&self->fork);
	if (print_msg(self->info, FORK, self->self_nb))
		return (pthread_mutex_unlock(&self->fork), EXIT_FAILURE);
	pthread_mutex_lock(&self->next->fork);
	if (print_msg(self->info, FORK, self->self_nb))
		return (pthread_mutex_unlock(&self->fork),
			pthread_mutex_unlock(&self->next->fork), EXIT_FAILURE);
	if (print_msg(self->info, EATING, self->self_nb))
		return (EXIT_FAILURE);
	usleep(self->info->t_to_eat * 1000);
	pthread_mutex_unlock(&self->fork);
	pthread_mutex_unlock(&self->next->fork);
	if (update_meal(self))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	usleep(self->start_wait);
	while (1)
	{
		if (philo_eat(self))
			return (NULL);
		print_msg(self->info, SLEEPING, self->self_nb);
		usleep(self->info->t_to_sleep * 1000);
		if (check_end(self->info))
			return (NULL);
		print_msg(self->info, THINKING, self->self_nb);
	}
	return (NULL);
}
