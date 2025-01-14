/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:16:28 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/14 14:59:30 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(t_philo_info *philo_info, int self_nb, int start_wait)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf("%s\n", ERROR_CREATE_PHILO_STRUCT), NULL);
	if (pthread_mutex_init(&new_philo->fork, NULL)
		|| pthread_mutex_init(&new_philo->meal_mutex, NULL))
		return (printf("%s\n", ERROR_INIT_SEM), NULL);
	new_philo->info = philo_info;
	new_philo->self_nb = self_nb;
	new_philo->start_wait = start_wait;
	new_philo->nb_meal = 0;
	new_philo->next = NULL;
	return (new_philo);
}

bool	philo_add_last(t_philo	**lst, t_philo	*philo)
{
	t_philo	*origin;

	if (!philo || !philo)
		return (EXIT_FAILURE);
	if (!*lst)
	{
		*lst = philo;
		philo->next = philo;
		return (EXIT_SUCCESS);
	}
	origin = *lst;
	while (origin->next != *lst)
		*lst = (*lst)->next;
	philo->next = (*lst)->next;
	(*lst)->next = philo;
	return (EXIT_SUCCESS);
}

void	philo_free(t_philo *lst)
{
	t_philo	*origin;
	t_philo	*tmp_philo;

	if (!lst)
		return ;
	origin = NULL;
	pthread_mutex_destroy(&lst->info->write_sem);
	pthread_mutex_destroy(&lst->info->time_sem);
	pthread_mutex_destroy(&lst->info->end_sem);
	while (origin != lst)
	{
		if (!origin)
			origin = lst;
		tmp_philo = lst;
		lst = lst->next;
		pthread_mutex_destroy(&tmp_philo->meal_mutex);
		free(tmp_philo);
	}
}

int	philo_size(t_philo *lst)
{
	t_philo	*origin;
	int		size;

	if (!lst)
		return (0);
	origin = lst;
	lst = lst->next;
	size = 1;
	while (origin != lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
