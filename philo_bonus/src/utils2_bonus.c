/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:49:50 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/01 12:29:55 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init2(t_philo **philos, t_info *info)
{
	int	i;

	*philos = (t_philo *)malloc(info->number_of_philo * sizeof(t_philo));
	i = 0;
	sem_unlink("/semaphore");
	sem_unlink("/die");
	sem_unlink("/print");
	while (i < info->number_of_philo)
	{
		((*philos)[i]).sem_start = sem_open("/sem_start", O_CREAT, 0644, 1);
		((*philos)[i]).index = i;
		((*philos)[i]).info = info;
		i++;
	}
	return (1);
}

void	kill_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->number_of_philo)
	{
		kill(philo->info->pid[i], SIGKILL);
		sem_close(philo[i].sem_start);
		sem_unlink("/sem_start");
		i++;
	}
	sem_close(philo->info->semaphore);
	sem_close(philo->info->sem_begin);
	sem_close(philo->info->print);
	sem_close(philo->info->die);
	sem_unlink("/semaphore");
	sem_unlink("/sem_begin");
	sem_unlink("/print");
	sem_unlink("/die");
}

void	*check_die(void	*ptr)
{
	t_philo			*philo;
	struct timeval	end;
	unsigned long	time;
	unsigned long	val;

	philo = (t_philo *)ptr;
	while (1)
	{
		usleep(50);
		gettimeofday(&end, NULL);
		sem_wait(philo->sem_start);
		val = (end.tv_usec - (philo->start).tv_usec) / 1000;
		time = (end.tv_sec - (philo->start).tv_sec) * 1000 + val;
		sem_post(philo->sem_start);
		val = philo->info->time_to_die;
		if (time > val)
		{
			sem_wait(philo->info->print);
			printf("%lu philo %d is died\n", gettime(philo), philo->index + 1);
			sem_post(philo->info->die);
			return (NULL);
		}
	}
	return (NULL);
}

void	create_process(t_philo *philos)
{
	int	i;

	i = 0;
	gettimeofday(&philos->info->begin, NULL);
	while (i < philos->info->number_of_philo)
	{
		gettimeofday(&(philos[i].start), NULL);
		philos->info->pid[i] = fork();
		if (philos->info->pid[i] == 0)
			life(&philos[i]);
		i++;
	}
}
