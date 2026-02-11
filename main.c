/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:51:16 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 15:19:14 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(t_rules	*rules, char **argv)
{
	memset(rules, 0, sizeof(t_rules));
	rules->nb_meal_max = -1;
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->nb_meal_max = ft_atoi(argv[5]);
	return ;
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	if (check_error(argc, argv))
		return (1);
	init_rules(&rules, argv);
	if (init_simulation(&rules, &philos))
		return (printf("Error: initialization failed\n"));
	if (run_simulation(&rules, philos))
		printf("Error: simulation failed\n");
	cleanup_simulation(&rules, philos);
	return (0);
}
