/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:48:57 by lchauvet          #+#    #+#             */
/*   Updated: 2025/01/10 18:01:24 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

long	ft_atol(const char *nptr)
{
	int		signe;
	long	resulte;

	signe = 1;
	resulte = 0;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signe = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		resulte = resulte * 10 + (*nptr - '0');
		nptr++;
	}
	return (resulte * signe);
}



bool	verif_param(int argc, char **argv)
{
	char	*arg;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	while (argc > 1)
	{
		arg = argv[argc - 1];
		if (ft_atol(arg) < 1)
			return (EXIT_FAILURE);
		if ((*arg == '-' || *arg == '+') && *arg != '\0')
			arg++;
		while (ft_isdigit(*arg))
			arg++;
		if (*arg != '\0')
			return (EXIT_FAILURE);
		argc--;
	}
	return (EXIT_SUCCESS);
}
