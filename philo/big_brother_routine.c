/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:20:53 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 17:40:49 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*big_brother_routine(void *arg)
{
	t_philo	*other;
	long	time;

	other = (t_philo *)arg;
	while (1)
	{
		time = get_time(other->info->time_mutex);
		if (time - other->last_eat >= other->info->t_to_die)
		{
			pthread_mutex_lock(other->info->write_mutex);
			printf("%li %i ", time - other->info->start_time, other->self_nb);
			printf(RED MSG_DIED END);
			return (NULL);
		}
		other = other->next;
	}
	return (NULL);
}
