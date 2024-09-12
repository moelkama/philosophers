/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:35:29 by moelkama          #+#    #+#             */
/*   Updated: 2023/05/25 20:44:56 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_begin;
	pthread_mutex_t	print;
	struct timeval	begin;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				how_many_eat;
}					t_info;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex_start;
	struct timeval	start;
	int				index;
	int				left;
	t_info			*info;
}					t_philo;

int				get_number(char *nbr);
int				ft_init(t_philo **philos, int c, char **v);
int				check_arg(t_info *info, int c);
unsigned long	gettime(t_philo *philo);
int				ft_init2(t_philo **philos, t_info *info);
void			destroy_mutexs(t_philo *philos);

#endif