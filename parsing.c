/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:51:21 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/06 15:30:16 by nbaldes          ###   ########.fr       */
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
