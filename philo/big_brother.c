/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:20:53 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/14 09:32:06 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*big_brother(t_philo *other)
{
	long	time;

	while (1)
	{
		time = get_time(&other->info->time_mutex);
		pthread_mutex_lock(&other->last_meat_mutex);
		if (time - other->last_meat >= other->info->t_to_die)
		{
			pthread_mutex_lock(&other->info->dead_mutex);
			other->info->is_dead = true;
			pthread_mutex_unlock(&other->info->dead_mutex);
			pthread_mutex_lock(&other->info->write_mutex);
			printf("%li %i ", time - other->info->start_time, other->self_nb);
			printf(RED MSG_DIED END);
			pthread_mutex_unlock(&other->info->write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&other->last_meat_mutex);

		other = other->next;
	}
	return (NULL);
}
