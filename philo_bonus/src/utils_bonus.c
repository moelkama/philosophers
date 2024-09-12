/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:35:39 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/01 12:28:39 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi(char *str)
{
	long	res;
	int		index;
	int		sign;

	res = 0;
	if (!str)
		return (2147483649);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	index = 0;
	while (res < 2147483648 && str[index] >= '0' && str[index] <= '9')
		res = res * 10 + (str[index++] - 48);
	return (res * sign);
}

int	get_number(char *nbr)
{
	long	nb;
	int		i;

	i = 0;
	while (nbr[i])
	{
		if (i != 0 && (nbr[i] > '9' || nbr[i] < '0'))
			return (-1);
		if (i == 0 && nbr[i] != '+' && nbr[i]
			!= '-' && (nbr[i] > '9' || nbr[i] < '0'))
			return (-1);
		i++;
	}
	nb = ft_atoi(nbr);
	if (nb > 2147483647 || nb < -2147483648)
		return (-1);
	return (nb);
}

int	check_arg(t_info *info, int c)
{
	if (info->number_of_philo < 0)
		return (0);
	if (info->time_to_die < 0)
		return (0);
	if (info->time_to_eat < 0)
		return (0);
	if (info->time_to_sleep < 0)
		return (0);
	if (c == 6 && info->how_many_eat < 0)
		return (0);
	return (1);
}

int	ft_init(t_philo **philos, int c, char **v)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof (t_info));
	info->number_of_philo = get_number(v[1]);
	info->time_to_die = get_number(v[2]);
	info->time_to_eat = get_number(v[3]);
	info->time_to_sleep = get_number(v[4]);
	if (c == 6)
		info->how_many_eat = get_number(v[5]);
	else
		info->how_many_eat = -1;
	if (!check_arg(info, c))
		return (0);
	return (ft_init2(philos, info));
}

unsigned long	gettime(t_philo *philo)
{
	struct timeval	time;
	long			begin;
	long			val;

	val = philo->info->begin.tv_usec / 1000;
	sem_wait(philo->info->sem_begin);
	begin = philo->info->begin.tv_sec * 1000 + val;
	sem_post(philo->info->sem_begin);
	gettimeofday(&time, NULL);
	return (-begin + time.tv_sec * 1000 + time.tv_usec / 1000);
}
