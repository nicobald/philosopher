/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:09:51 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 15:19:30 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_last_meal(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		philos[i].lmeal = rules->start_time;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
}

int	create_philo_threads(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]))
		{
			set_stop(rules, 1);
			break ;
		}
		i++;
	}
	return (i);
}

void	join_created_threads(t_philo *philos, int created)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	create_monitor(t_rules *rules,
			t_philo *philos, pthread_t *monitor)
{
	t_monitor_args	args;

	args.rules = rules;
	args.philos = philos;
	if (pthread_create(monitor, NULL,
			monitor_routine, &args))
	{
		set_stop(rules, 1);
		return (1);
	}
	return (0);
}

int	run_simulation(t_rules *rules, t_philo *philos)
{
	pthread_t	monitor;
	int			created;

	rules->start_time = now_ms();
	init_last_meal(rules, philos);
	created = create_philo_threads(rules, philos);
	if (created != rules->nb_philo)
	{
		join_created_threads(philos, created);
		return (1);
	}
	if (create_monitor(rules, philos, &monitor))
	{
		join_created_threads(philos, rules->nb_philo);
		return (1);
	}
	join_created_threads(philos, rules->nb_philo);
	pthread_join(monitor, NULL);
	return (0);
}
