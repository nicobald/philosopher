/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:51:11 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 15:55:14 by nbaldes          ###   ########.fr       */
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

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	long long		start_time;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				nb_meal;
	long long		lmeal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

typedef struct s_monitor_args
{
	int		i;
	t_rules	*rules;
	t_philo	*philos;
}	t_monitor_args;

//utils
int			ft_atoi(const char *str);
int			get_stop(t_rules *rules);
void		set_stop(t_rules *rules, int value);
void		msleep_precise(long long duration_ms, t_rules *rules);
long long	now_ms(void);

//parsing
int			check_error(int argc, char **argv);

//init
int			init_simulation(t_rules *rules, t_philo **philos);

//log
void		log_action(t_philo *philo, const char *msg);
void		log_death(t_philo *philo);
void		handle_single_philo(t_philo *philo);
void		lock_forks(t_philo *philo);

//philo
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);

//simulation
int			run_simulation(t_rules *rules, t_philo *philos);

//free
void		cleanup_simulation(t_rules *rules, t_philo *philos);

#endif