/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:45:09 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/02 17:11:56 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	sign = 1;
	i = 0;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void precise_usleep(long long time_in_ms, t_table *table)
{
	long long start = get_time();
	while (!table->dead)
	{
		if (get_time() - start >= time_in_ms)
			break ;
		usleep(50);
	}
}

void		action_print(t_table *table, int id, char *string)
{
	pthread_mutex_lock(&(table->print));
	if (!(table->dead))
	{
		printf("%lli ", get_time() - table->start);
		printf("%i ", id);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(table->print));
	return ;
}
