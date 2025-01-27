/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:31 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/27 11:19:41 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_param(int argc, char **argv, t_philo_info *philo_info)
{
	philo_info->nb_philo = ft_atol(argv[1]);
	philo_info->t_to_die = ft_atol(argv[2]);
	philo_info->t_to_eat = ft_atol(argv[3]);
	philo_info->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		philo_info->nb_must_eat = ft_atol(argv[5]);
	else
		philo_info->nb_must_eat = -1;
	if (pthread_mutex_init(&philo_info->time_mutex, NULL)
		|| pthread_mutex_init(&philo_info->write_mutex, NULL)
		|| pthread_mutex_init(&philo_info->end_mutex, NULL)
		|| pthread_mutex_init(&philo_info->nb_philo_mutex, NULL))
		return (printf("%s\n", ERROR_INIT_MUTEX), EXIT_FAILURE);
	philo_info->is_ended = false;
	philo_info->start_time = 0;
	return (EXIT_SUCCESS);
}

bool	print_msg(t_philo_info *philo_info, short type, int self)
{
	long	time;

	pthread_mutex_lock(&philo_info->write_mutex);
	time = get_time(philo_info);
	if (time == -1)
		return (pthread_mutex_unlock(&philo_info->write_mutex), EXIT_FAILURE);
	if (check_end(philo_info))
		return (pthread_mutex_unlock(&philo_info->write_mutex), EXIT_FAILURE);
	printf("%li %i ", time - philo_info->start_time, self);
	if (type == FORK)
		printf(GREY MSG_FORK END);
	else if (type == EATING)
		printf(GREEN MSG_EATING END);
	else if (type == SLEEPING)
		printf(BLUE MSG_SLEEPING END);
	else if (type == THINKING)
		printf(WHITE MSG_THINKING END);
	pthread_mutex_unlock(&philo_info->write_mutex);
	return (EXIT_SUCCESS);
}

long	get_time(t_philo_info *info)
{
	struct timeval	timeval;

	pthread_mutex_lock(&info->time_mutex);
	if (check_end(info))
		return (pthread_mutex_unlock(&info->time_mutex), -1);
	gettimeofday(&timeval, NULL);
	pthread_mutex_unlock(&info->time_mutex);
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
		return (philo_free(philo), EXIT_FAILURE);
	philo_free(philo);
	return (EXIT_SUCCESS);
}
