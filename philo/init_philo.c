/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:49:43 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 15:46:09 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	_init_struct(t_philo **philo, t_philo_info *philo_info)
{
	int		counter;
	bool	thread_type;

	counter = 0;
	while (counter != philo_info->nb_philo)
	{
		if (counter % 2 != 0)
			thread_type = 1;
		else
			thread_type = 0;
		if (philo_add_last(philo,
				philo_new(philo_info, counter + 1, thread_type)))
			return (EXIT_FAILURE);
		counter++;
	}
	return (EXIT_SUCCESS);
}

static bool	_init_pthread(t_philo *philo, int nb_philo)
{
	int		counter;

	counter = 0;
	while (counter != nb_philo)
	{
		if (pthread_create(&philo->philo, NULL, philo_routine, philo))
			return (printf("%s\n", ERROR_CREATE_PHILO), NULL);
		philo = philo->next;
		counter++;
	}
	return (EXIT_SUCCESS);
}

bool	_init_join(t_philo *philo, int nb_philo)
{
	int	counter;

	counter = 0;
	while (counter != nb_philo)
	{
		if (pthread_join(philo->philo, NULL))
			return (printf("%s\n", ERROR_INIT_JOIN), EXIT_FAILURE);
		philo = philo->next;
		counter++;
	}
	return (EXIT_SUCCESS);
}

bool	get_philo(t_philo **philo, t_philo_info *philo_info)
{

	if (_init_struct(philo, philo_info))
		return (EXIT_FAILURE);
	if (_init_pthread(*philo, philo_info->nb_philo))
		return (EXIT_FAILURE);
	if (_init_join(*philo, philo_info->nb_philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
