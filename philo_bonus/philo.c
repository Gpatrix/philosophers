/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:31 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/15 13:54:53 by lchauvet         ###   ########.fr       */
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
	philo_info->fork_sem = sem_open("fork", O_CREAT | O_EXCL,
			philo_info->nb_philo);
	philo_info->time_sem = sem_open("time", O_CREAT | O_EXCL, 1);
	philo_info->write_sem = sem_open("write", O_CREAT | O_EXCL, 1);
	philo_info->end_sem = sem_open("end", O_CREAT | O_EXCL, 1);
	if (philo_info->fork_sem == SEM_FAILED
		|| philo_info->time_sem == SEM_FAILED
		|| philo_info->write_sem == SEM_FAILED
		|| philo_info->end_sem == SEM_FAILED)
		return (printf("%s\n", ERROR_INIT_SEM), EXIT_FAILURE);
	philo_info->is_ended = false;
	philo_info->start_time = 0;
	return (EXIT_SUCCESS);
}

bool	print_msg(t_philo_info *philo_info, short type, int self)
{
	long	time;

	sem_wait(&philo_info->write_sem);
	if (check_end(philo_info))
		return (sem_post(&philo_info->write_sem), EXIT_FAILURE);
	time = get_time(philo_info);
	if (time == -1)
		return (sem_post(&philo_info->write_sem), EXIT_FAILURE);
	printf("%li %i ", time - philo_info->start_time, self);
	if (type == FORK)
		printf(GREY MSG_FORK END);
	else if (type == EATING)
		printf(GREEN MSG_EATING END);
	else if (type == SLEEPING)
		printf(BLUE MSG_SLEEPING END);
	else if (type == THINKING)
		printf(WHITE MSG_THINKING END);
	sem_post(&philo_info->write_sem);
	return (EXIT_SUCCESS);
}

long	get_time(t_philo_info *info)
{
	struct timeval	timeval;

	sem_wait(&info->time_sem);
	if (check_end(info))
		return (sem_post(&info->time_sem), -1);
	gettimeofday(&timeval, NULL);
	sem_post(&info->time_sem);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	single_philo(t_philo_info *philo_info)
{
	printf("0 1 "GREY"has taken a fork\n"END);
	usleep(philo_info->t_to_die * 1000);
	printf("%li 1 "RED"died\n"END, philo_info->t_to_die);
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
	if (philo_info.nb_philo == 1)
		single_philo(&philo_info);
	else
	{
		if (get_philo(&philo, &philo_info))
			return (EXIT_FAILURE);
		philo_free(philo);
	}
	return (EXIT_SUCCESS);
}
