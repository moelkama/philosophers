/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:31:00 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/01 12:24:29 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleeptime(int time)
{
	struct timeval	t;
	long			i;

	gettimeofday(&t, 0);
	i = t.tv_sec * 1000 + t.tv_usec / 1000;
	while ((t.tv_sec * 1000 + t.tv_usec / 1000) - i < time)
	{
		usleep(50);
		gettimeofday(&t, 0);
	}
}

void	continue_life(t_philo *philo, unsigned long time)
{
	sem_wait(philo->sem_start);
	gettimeofday(&philo->start, NULL);
	sem_post(philo->sem_start);
	sem_wait(philo->info->print);
	printf("%lu ms philo %d is eating\n", time, philo->index + 1);
	sem_post(philo->info->print);
	ft_sleeptime(philo->info->time_to_eat);
	sem_post(philo->info->semaphore);
	sem_post(philo->info->semaphore);
	time = gettime(philo);
	sem_wait(philo->info->print);
	printf("%lu ms philo %d is sleep\n", time, philo->index + 1);
	sem_post(philo->info->print);
	ft_sleeptime(philo->info->time_to_sleep);
	time = gettime(philo);
	sem_wait(philo->info->print);
	printf("%lu ms philo %d is thinking\n", time, philo->index + 1);
	sem_post(philo->info->print);
}

void	life(t_philo *philo)
{
	unsigned long	time;
	int				eat;

	pthread_create(&philo->thread, NULL, check_die, philo);
	if ((philo->index + 1) % 2 == 0)
		usleep(100);
	eat = 0;
	while (philo->info->how_many_eat == -1 || eat < philo->info->how_many_eat)
	{
		sem_wait(philo->info->semaphore);
		time = gettime(philo);
		sem_wait(philo->info->print);
		printf("%lu ms philo %d take a fork\n", time, philo->index + 1);
		sem_post(philo->info->print);
		sem_wait(philo->info->semaphore);
		time = gettime(philo);
		sem_wait(philo->info->print);
		printf("%lu ms philo %d take a fork\n", time, philo->index + 1);
		sem_post(philo->info->print);
		continue_life(philo, time);
		eat++;
	}
	sem_post(philo->info->die);
	exit(0);
}

int	main(int c, char **v)
{
	t_philo	*philos;

	if (c == 6 || c == 5)
	{
		if (ft_init(&philos, c, v))
		{
			philos->info->die = sem_open("/die", O_CREAT, 0644, 1);
			sem_wait(philos->info->die);
			philos->info->pid = malloc(philos->info->number_of_philo * 4);
			philos->info->semaphore = sem_open("/semaphore", O_CREAT, 0644,
					philos->info->number_of_philo);
			philos->info->print = sem_open("/print", O_CREAT, 0644, 1);
			create_process(philos);
			sem_wait(philos->info->die);
			kill_process(philos);
		}
		else
			write(2, "invalid argement!\n", 19);
	}
	else
		write(2, "check the number of argemts!\n", 29);
}
