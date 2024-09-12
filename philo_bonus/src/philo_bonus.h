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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_info
{
	sem_t			*semaphore;
	sem_t			*sem_begin;
	sem_t			*print;
	sem_t			*die;
	struct timeval	begin;
	int				*pid;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				how_many_eat;
}					t_info;

typedef struct s_philo
{
	pthread_t		thread;
	sem_t			*sem_start;
	struct timeval	start;
	int				index;
	t_info			*info;
}					t_philo;

void			create_process(t_philo *philos);
void			kill_process(t_philo *philo);
int				get_number(char *nbr);
int				ft_init(t_philo **philos, int c, char **v);
int				check_arg(t_info *info, int c);
unsigned long	gettime(t_philo *philo);
void			life(t_philo *philo);
void			*check_die(void *ptr);
int				ft_init2(t_philo **philos, t_info *info);

#endif