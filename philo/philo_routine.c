/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:18:52 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/30 09:06:04 by lchauvet         ###   ########.fr       */
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

bool	check_single_philo(t_philo *self)
{
	pthread_mutex_lock(&self->info->nb_philo_mutex);
	if (self->info->nb_philo == 1)
	{
		pthread_mutex_lock(&self->fork);
		pthread_mutex_lock(&self->info->write_mutex);
		printf("0 1 "GREY"has taken a fork\n"END);
		pthread_mutex_unlock(&self->info->write_mutex);
		usleep(self->info->t_to_die * 1000);
		pthread_mutex_unlock(&self->fork);
		pthread_mutex_unlock(&self->info->nb_philo_mutex);
		return (EXIT_FAILURE);
	}
	else
		return (pthread_mutex_unlock(&self->info->nb_philo_mutex),
			EXIT_SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	if (check_single_philo(self))
		return (NULL);
	if (self->self_nb % 2 == 0)
		usleep(15000);
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
