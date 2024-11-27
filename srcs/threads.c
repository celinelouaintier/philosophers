/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-27 13:22:33 by clouaint          #+#    #+#             */
/*   Updated: 2024-11-27 13:22:33 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!table->dead)
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_lock(&table->print);
			if (get_time() - table->philos[i].last_eat > table->time_to_die)
			{
				printf("%lld %d died\n", get_time() - table->start, table->philos[i].id);
				table->dead = 1;
				pthread_mutex_unlock(&table->print);
				break ;
			}
			pthread_mutex_unlock(&table->print);
			usleep(1000);
			i++;
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d is thinking\n", get_time() - philo->table->start, philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor_t;
	int			ret;

	i = 0;
	while (i < table->philo_count)
	{
		ret = pthread_create(&table->philos[i].thread, NULL, &routine, &table->philos[i]);
		if (ret != 0)
			return (1);
		i++;
	}
	ret = pthread_create(&monitor_t, NULL, (void *) monitor, table);
	if (ret != 0)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		ret = pthread_join(table->philos[i].thread, NULL);
		if (ret != 0)
			return (1);
		i++;
	}
	ret = pthread_join(monitor_t, NULL);
	if (ret != 0)
		return (1);
	return (0);
}
