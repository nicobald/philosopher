/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:33:22 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 15:16:16 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->lmeal = now_ms();
	philo->nb_meal += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	log_action(philo, "is eating");
	msleep_precise(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->left_fork != philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	log_action(philo, "is sleeping");
	msleep_precise(philo->rules->time_to_sleep, philo->rules);
	log_action(philo, "is thinking");
	if (philo->rules->nb_philo % 2 == 1)
		msleep_precise(philo->rules->time_to_eat / 2, philo->rules);
}

int	all_fed(t_rules *rules, t_philo *philos)
{
	int	i;

	if (rules->nb_meal_max < 0)
		return (0);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].nb_meal < rules->nb_meal_max)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_monitor_args	*d;

	d = (t_monitor_args *)arg;
	while (!get_stop(d->rules))
	{
		d->i = -1;
		while (++d->i < d->rules->nb_philo && !get_stop(d->rules))
		{
			pthread_mutex_lock(&d->philos[d->i].meal_mutex);
			if (now_ms() - d->philos[d->i].lmeal >= d->rules->time_to_die)
			{
				log_death(&d->philos[d->i]);
				pthread_mutex_unlock(&d->philos[d->i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&d->philos[d->i].meal_mutex);
		}
		if (all_fed(d->rules, d->philos))
		{
			set_stop(d->rules, 1);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->nb_philo == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->rules->time_to_eat * 500);
	while (!get_stop(philo->rules))
	{
		lock_forks(philo);
		if (philo->left_fork == philo->right_fork)
			break ;
		eat(philo);
		if (get_stop(philo->rules))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
