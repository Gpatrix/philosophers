/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:31 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/13 17:40:27 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_param(int argc, char **argv, t_philo_info *philo_info)
{
	static pthread_mutex_t	time_mutex;
	static pthread_mutex_t	write_mutex;

	philo_info->nb_philo = ft_atol(argv[1]);
	philo_info->t_to_die = ft_atol(argv[2]);
	philo_info->t_to_eat = ft_atol(argv[3]);
	philo_info->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		philo_info->nb_must_eat = ft_atol(argv[5]);
	else
		philo_info->nb_must_eat = -1;
	if (pthread_mutex_init(&time_mutex, NULL))
		return (printf("%s\n", ERROR_INIT_MUTEX), EXIT_FAILURE);
	if (pthread_mutex_init(&write_mutex, NULL))
		return (printf("%s\n", ERROR_INIT_MUTEX), EXIT_FAILURE);
	philo_info->time_mutex = &time_mutex;
	philo_info->write_mutex = &write_mutex;
	philo_info->start_time = 0;
	return (EXIT_SUCCESS);
}

long	get_time(pthread_mutex_t *time_mutex)
{
	struct timeval	timeval;

	pthread_mutex_lock(time_mutex);
	gettimeofday(&timeval, NULL);
	pthread_mutex_unlock(time_mutex);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philo;

	philo = NULL;
	if (verif_param(argc, argv))
		return (printf("%s\n", ERROR_PARAM), EXIT_FAILURE);
	if (get_param(argc, argv, &philo_info))
		return (EXIT_FAILURE);
	if (get_philo(&philo, &philo_info))
		return (EXIT_FAILURE);
	// philo_free(philo);
	return (EXIT_SUCCESS);
}
