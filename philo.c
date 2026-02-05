/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:51:16 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/05 17:28:51 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_var(t_glob *glob, char **argv)
{
	glob->start_time = 0;
	glob->args.nb_philo = ft_atoi(argv[1]);
	glob->args.t_die = ft_atoi(argv[2]);
	glob->args.t_eat = ft_atoi(argv[3]);
	glob->args.t_sleep = ft_atoi(argv[4]);
	glob->args.nb_meal = -1;
	if (argv[5])
		glob->args.nb_meal = ft_atoi(argv[5]);
	return ;
}

int	check_error(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(1, "invalid number of arg\n", 23));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Error : wrong arg format"));
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (printf("Error : invalid number of philosopher"));
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (printf("Error : time must be positive"));
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

int	init_thread(int *thread, t_glob *glob, int philosopher(), int *philo)
{
	int	i;

	while (i < glob->args.nb_philo)
	{
		pthread_create(&thread[i], NULL, philosopher, &glob->philo[i]);
		i++;
	}
	return (0);
}

int	init_mutex(t_glob *glob)
{
	pthread_mutex_init(&glob->death_mutex, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	int		thread[200];
	int		*philo;
	t_glob	glob;

	if (check_error(argc, argv))
		return (1);
	init_var(&glob, argv);
	// glob.start_time = current_time_ms();
	// init_thread(thread, &glob, philosopher(), philo);
	init_mutex(&glob);
	return (0);
}

