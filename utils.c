/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:59:49 by nbaldes           #+#    #+#             */
/*   Updated: 2026/02/11 14:01:23 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	get_stop(t_rules *rules)
{
	int	value;

	pthread_mutex_lock(&rules->stop_mutex);
	value = rules->stop;
	pthread_mutex_unlock(&rules->stop_mutex);
	return (value);
}

void	set_stop(t_rules *rules, int value)
{
	pthread_mutex_lock(&rules->stop_mutex);
	rules->stop = value;
	pthread_mutex_unlock(&rules->stop_mutex);
}

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	msleep_precise(long long duration_ms, t_rules *rules)
{
	long long	start;
	long long	elapsed;
	long long	remaining;
	long long	sleep_time;

	start = now_ms();
	while (!get_stop(rules))
	{
		elapsed = now_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		remaining = duration_ms - elapsed;
		if (remaining > 10)
			sleep_time = remaining * 500;
		else
			sleep_time = 100;
		usleep(sleep_time);
	}
}
