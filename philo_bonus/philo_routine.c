/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:18:52 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/15 13:39:17 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_end(t_philo_info *info)
{
	sem_wait(&info->end_sem);
	if (info->is_ended == true)
		return (sem_post(&info->end_sem), true);
	else
		return (sem_post(&info->end_sem), false);
}

bool	update_meal(t_philo *self)
{
	sem_wait(&self->meal_sem);
	self->last_meal = get_time(self->info);
	self->nb_meal++;
	sem_post(&self->meal_sem);
	if (self->last_meal == -1 || verif_meal(self))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	philo_eat(t_philo *self)
{
	sem_wait(&self->info->fork_sem);
	if (print_msg(self->info, FORK, self->self_nb))
		return (sem_post(&self->info->fork_sem), EXIT_FAILURE);
	sem_wait(&self->info->fork_sem);
	if (print_msg(self->info, FORK, self->self_nb))
		return (sem_post(&self->info->fork_sem),
			sem_post(&self->next->info->fork_sem), EXIT_FAILURE);
	if (print_msg(self->info, EATING, self->self_nb))
		return (EXIT_FAILURE);
	usleep(self->info->t_to_eat * 1000);
	sem_post(&self->info->fork_sem);
	sem_post(&self->next->info->fork_sem);
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
