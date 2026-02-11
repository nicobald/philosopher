/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:30:54 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 14:46:09 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_rules *rules)
{
	if (pthread_mutex_init(&rules->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->stop_mutex);
		return (1);
	}
	return (0);
}

int	init_forks(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&rules->forks[i]);
			}
			free(rules->forks);
			rules->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philosophers(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meal = 0;
		philos[i].lmeal = 0;
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&philos[i].meal_mutex);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_simulation(t_rules *rules, t_philo **philos)
{
	if (init_mutexes(rules))
	{
		printf("mauvais init mutex\n");
		return (1);
	}
	if (init_forks(rules))
	{
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->stop_mutex);
		return (1);
	}
	*philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!*philos)
	{
		cleanup_simulation(rules, NULL);
		return (1);
	}
	if (init_philosophers(rules, *philos))
	{
		free(*philos);
		*philos = NULL;
		cleanup_simulation(rules, NULL);
		return (1);
	}
	return (0);
}

void	cleanup_simulation(t_rules *rules, t_philo *philos)
{
	int	i;

	if (philos)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			pthread_mutex_destroy(&philos[i].meal_mutex);
			i++;
		}
		free(philos);
	}
	if (rules->forks)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			i++;
		}
		free(rules->forks);
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->stop_mutex);
}
