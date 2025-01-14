/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:49:43 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/14 12:09:45 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	_init_struct(t_philo **philo, t_philo_info *philo_info)
{
	int		counter;
	int		start_wait;

	counter = 0;
	while (counter != philo_info->nb_philo)
	{
		if (counter % 2 != 0)
			start_wait = 15000;
		else
			start_wait = 0;
		if (philo_add_last(philo,
				philo_new(philo_info, ++counter, start_wait)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool	_init_pthread(t_philo *philo, int nb_philo)
{
	int		counter;

	counter = 0;
	philo->info->start_time = get_time(philo->info);
	while (counter != nb_philo)
	{
		if (pthread_create(&philo->philo, NULL, philo_routine, philo))
			return (printf("%s\n", ERROR_CREATE_PHILO), EXIT_FAILURE);
		philo->last_meal = get_time(philo->info);
		philo = philo->next;
		counter++;
	}
	return (EXIT_SUCCESS);
}

static void	_wait_philo(t_philo *philo)
{
	int	counter;

	counter = 0;
	while (counter != philo->info->nb_philo)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
		counter++;
	}
}

bool	get_philo(t_philo **philo, t_philo_info *philo_info)
{
	if (_init_struct(philo, philo_info))
		return (EXIT_FAILURE);
	if (_init_pthread(*philo, philo_info->nb_philo))
		return (EXIT_FAILURE);
	if (big_brother(*philo))
		return (printf("%s\n", ERROR_INIT_JOIN), EXIT_FAILURE);
	_wait_philo(*philo);
	return (EXIT_SUCCESS);
}
