/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:41:54 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/01 12:55:10 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init2(t_philo **philos, t_info *info)
{
	int	i;

	info->mutex = malloc(info->number_of_philo * sizeof (pthread_mutex_t));
	*philos = (t_philo *)malloc(info->number_of_philo * sizeof(t_philo));
	(*philos)->info = NULL;
	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_mutex_init(&(info->mutex)[i], NULL);
		pthread_mutex_init(&(((*philos)[i]).mutex_start), NULL);
		((*philos)[i]).index = i;
		((*philos)[i]).info = info;
		((*philos)[i]).left = i + 1;
		if (i + 1 == info->number_of_philo)
			((*philos)[i]).left = 0;
		i++;
	}
	return (1);
}

void	destroy_mutexs(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->number_of_philo)
	{
		pthread_mutex_destroy(&philos[i].mutex_start);
		pthread_mutex_destroy(&philos->info->mutex[i]);
		pthread_detach(philos[i].thread);
		i++;
	}
	pthread_mutex_destroy(&philos->info->mutex_begin);
	pthread_mutex_destroy(&philos->info->print);
}
