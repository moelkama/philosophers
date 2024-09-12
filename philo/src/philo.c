/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:35:16 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/01 12:56:01 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *philos)
{
	struct timeval	end;
	unsigned long	time;
	unsigned long	val;
	int				i;

	while (1)
	{
		i = -1;
		while (++i < philos->info->number_of_philo)
		{
			gettimeofday(&end, NULL);
			pthread_mutex_lock(&((philos[i]).mutex_start));
			val = (end.tv_usec - (philos[i].start).tv_usec) / 1000;
			time = (end.tv_sec - (philos[i].start).tv_sec) * 1000 + val;
			pthread_mutex_unlock(&((philos[i]).mutex_start));
			val = philos->info->time_to_die;
			if (time > val)
			{
				pthread_mutex_lock(&(philos->info->print));
				printf("%lu philo %d is died\n", gettime(&philos[i]), i + 1);
				return (0);
			}
		}
	}
	return (0);
}

void	ft_sleeptime(int time)
{
	struct timeval	t;
	long			i;

	gettimeofday(&t, 0);
	i = t.tv_sec * 1000 + t.tv_usec / 1000;
	while ((t.tv_sec * 1000 + t.tv_usec / 1000) - i < time)
	{
		usleep(50);
		gettimeofday(&t, NULL);
	}
}

void	continue_life(t_philo *philo, unsigned long time)
{
	pthread_mutex_lock(&philo->mutex_start);
	gettimeofday(&philo->start, NULL);
	pthread_mutex_unlock(&philo->mutex_start);
	pthread_mutex_lock(&philo->info->print);
	printf("%lu ms philo %d is eating\n", time, philo->index + 1);
	pthread_mutex_unlock(&philo->info->print);
	ft_sleeptime(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->mutex[philo->index]);
	pthread_mutex_unlock(&philo->info->mutex[philo->left]);
	time = gettime(philo);
	pthread_mutex_lock(&philo->info->print);
	printf("%lu ms philo %d is sleeping\n", time, philo->index + 1);
	pthread_mutex_unlock(&philo->info->print);
	ft_sleeptime(philo->info->time_to_sleep);
	time = gettime(philo);
	pthread_mutex_lock(&philo->info->print);
	printf("%lu ms philo %d is thinking\n", time, philo->index + 1);
	pthread_mutex_unlock(&philo->info->print);
}

void	*life(void *ptr)
{
	t_philo			*philo;
	unsigned long	time;
	int				eat;

	philo = (t_philo *)ptr;
	if ((philo->index + 1) % 2 == 0)
		usleep(100);
	eat = 0;
	while (philo->info->how_many_eat == -1 || eat < philo->info->how_many_eat)
	{
		pthread_mutex_lock(&philo->info->mutex[philo->index]);
		time = gettime(philo);
		pthread_mutex_lock(&philo->info->print);
		printf("%lu ms philo %d has taken a fork\n", time, philo->index + 1);
		pthread_mutex_unlock(&philo->info->print);
		pthread_mutex_lock(&philo->info->mutex[philo->left]);
		time = gettime(philo);
		pthread_mutex_lock(&philo->info->print);
		printf("%lu ms philo %d has taken a fork\n", time, philo->index + 1);
		pthread_mutex_unlock(&philo->info->print);
		continue_life(philo, time);
		eat++;
	}
	return (NULL);
}

int	main(int c, char **v)
{
	t_philo	*philos;
	int		i;

	if (c == 6 || c == 5)
	{
		if (ft_init(&philos, c, v))
		{
			i = 0;
			pthread_mutex_init(&(philos->info->print), NULL);
			pthread_mutex_init(&(philos->info->mutex_begin), NULL);
			gettimeofday(&philos->info->begin, NULL);
			while (i < philos->info->number_of_philo)
			{
				gettimeofday(&(philos[i].start), NULL);
				pthread_create(&(philos[i].thread), NULL, &life, &(philos[i]));
				i++;
			}
			check_die(philos);
			destroy_mutexs(philos);
		}
		else
			write(2, "invalid argement!\n", 19);
	}
	else
		write(2, "check the number of argemts!\n", 29);
}
