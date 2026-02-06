/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:51:16 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/06 15:28:18 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(int argc, char **argv)
{
	int		i;
	int		j;

	i = 2;
	if (argc < 5 || argc > 6)
		return (write(1, "invalid number of arg\n", 23));
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (printf("Error : time must be positive\n"));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Error : wrong arg format\n"));
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (printf("Error : invalid number of philosopher\n"));
	return (0);
}

long long	current_time_ms(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

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
		philos[i].timer_lmeal = 0;
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

int	init_simulation(t_rules *rules, t_philo **philos)
{
	if (init_mutexes(rules))
		return (1);
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

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	if (check_error(argc, argv))
		return (1);
	if (init_simulation(&rules, &philos))
		return (printf("Error: initialization failed\n"));
	// if (run_simulation())
	// 	ft_putstr_fd("Error: simulation failed\n", 2);
	cleanup_simulation(&rules, philos);
	return (0);
}

