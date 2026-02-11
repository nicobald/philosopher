/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:49:11 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 15:16:20 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_philo *philo, const char *msg)
{
	long long	ts;

	if (get_stop(philo->rules))
		return ;
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!get_stop(philo->rules))
	{
		ts = now_ms() - philo->rules->start_time;
		printf("%lld %d %s\n", ts, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	log_death(t_philo *philo)
{
	long long	ts;

	pthread_mutex_lock(&philo->rules->stop_mutex);
	if (philo->rules->stop)
	{
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		return ;
	}
	philo->rules->stop = 1;
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	pthread_mutex_lock(&philo->rules->print_mutex);
	ts = now_ms() - philo->rules->start_time;
	printf("%lld %d died\n", ts, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_action(philo, "has taken a fork");
	msleep_precise(philo->rules->time_to_die + 1, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(first);
	log_action(philo, "has taken a fork");
	if (first == second)
		return ;
	pthread_mutex_lock(second);
	log_action(philo, "has taken a fork");
}
