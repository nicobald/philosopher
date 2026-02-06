/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:51:11 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/06 10:07:36 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arg
{
	int	nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_meal;
}		t_arg;

typedef struct s_philo
{
	pthread_mutex_t	left_fork;
	pthread_mutex_t	how_fat_ru;

}		t_philo;

typedef struct s_glob
{
	pthread_mutex_t	death_mutex;
	pthread_mutex_t print_mutex;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	t_arg			args;
	int				someone_die;
	long long		start_time;
}		t_glob;

//utils

int	ft_atoi(const char *str);


#endif