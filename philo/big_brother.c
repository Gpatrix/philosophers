/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:20:53 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/15 14:02:49 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	_verif_dead(t_philo *other)
{
	long	time;

	time = get_time(other->info);
	pthread_mutex_lock(&other->meal_mutex);
	if (time - other->last_meal > other->info->t_to_die)
	{
		pthread_mutex_lock(&other->info->end_mutex);
		other->info->is_ended = true;
		pthread_mutex_unlock(&other->info->end_mutex);
		pthread_mutex_lock(&other->info->write_mutex);
		printf("%li %i ", time - other->info->start_time, other->self_nb);
		printf(RED MSG_DIED END);
		pthread_mutex_unlock(&other->info->write_mutex);
		pthread_mutex_unlock(&other->meal_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&other->meal_mutex);
	return (EXIT_SUCCESS);
}

bool	verif_meal(t_philo *other)
{
	int	philo_counter;

	philo_counter = 0;
	if (other->info->nb_must_eat == -1)
		return (false);
	while (philo_counter != other->info->nb_philo)
	{
		pthread_mutex_lock(&other->meal_mutex);
		if (other->nb_meal < other->info->nb_must_eat)
			return (pthread_mutex_unlock(&other->meal_mutex), false);
		pthread_mutex_unlock(&other->meal_mutex);
		other = other->next;
		philo_counter++;
	}
	pthread_mutex_lock(&other->info->end_mutex);
	other->info->is_ended = true;
	pthread_mutex_unlock(&other->info->end_mutex);
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
