/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:09:51 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 16:03:44 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_lmeal(t_rules *rules, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		philos[i].lmeal = rules->start_time;
		pthread_mutex_unlock(&philos[i].meal_mutex);
	}
}

int	create_threads_philo(t_rules *rules, t_philo *philos)
{
	int	i;
	int	created;

	created = 0;
	i = -1;
	while (++i < rules->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			set_stop(rules, 1);
			break ;
		}
		created++;
	}
	return (created);
}

void	join_thread(t_philo *philos, int nb_thread)
{
	int	i;

	i = -1;
	while (++i < nb_thread)
		pthread_join(philos[i].thread, NULL);
}

int	run_simulation(t_rules *rules, t_philo *philos)
{
	pthread_t		monitor;
	t_monitor_args	args;
	int				created;

	rules->start_time = now_ms();
	init_lmeal(rules, philos);
	created = create_threads_philo(rules, philos);
	if (created != rules->nb_philo)
	{
		join_thread(philos, created);
		return (1);
	}
	args.rules = rules;
	args.philos = philos;
	if (pthread_create(&monitor, NULL, monitor_routine, &args))
	{
		set_stop(rules, 1);
		join_thread(philos, rules->nb_philo);
		return (1);
	}
	join_thread(philos, rules->nb_philo);
	pthread_join(monitor, NULL);
	return (0);
}