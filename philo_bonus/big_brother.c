/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:20:53 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/15 14:03:15 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	_verif_dead(t_philo *other)
{
	long	time;

	time = get_time(other->info);
	sem_wait(&other->meal_sem);
	if (time - other->last_meal > other->info->t_to_die)
	{
		sem_wait(&other->info->end_sem);
		other->info->is_ended = true;
		sem_post(&other->info->end_sem);
		sem_wait(&other->info->write_sem);
		printf("%li %i ", time - other->info->start_time, other->self_nb);
		printf(RED MSG_DIED END);
		sem_post(&other->info->write_sem);
		sem_post(&other->meal_sem);
		return (EXIT_FAILURE);
	}
	sem_post(&other->meal_sem);
	return (EXIT_SUCCESS);
}

bool	verif_meal(t_philo *other)
{
	int	philo_counter;

	if (other->info->nb_must_eat == -1)
		return (false);
	philo_counter = 0;
	while (philo_counter != other->info->nb_philo)
	{
		sem_wait(&other->meal_sem);
		if (other->nb_meal < other->info->nb_must_eat)
			return (sem_post(&other->meal_sem), false);
		sem_post(&other->meal_sem);
		other = other->next;
		philo_counter++;
	}
	sem_wait(&other->info->end_sem);
	other->info->is_ended = true;
	sem_post(&other->info->end_sem);
	return (true);
}

void	*big_brother(t_philo *other)
{
	while (1)
	{
		if (_verif_dead(other))
			break ;
		if (check_end(other->info))
			break ;
		other = other->next;
	}
	return (NULL);
}
