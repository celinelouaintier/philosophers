/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:22:33 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/02 17:57:40 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->dead_lock);
	status = table->dead;
	pthread_mutex_unlock(&table->dead_lock);
	return (status);
}

void	set_dead(t_table *table)
{
	pthread_mutex_lock(&table->dead_lock);
	table->dead = 1;
	pthread_mutex_unlock(&table->dead_lock);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			if (has_eaten(&table->philos[i], i))
				return (NULL);
			if (get_time() - table->philos[i].last_eat > table->time_to_die)
			{
				action_print(table, table->philos[i].id, "died");
				set_dead(table);
				return (NULL);
			}
			pthread_mutex_unlock(&table->meal_check);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(15000);
	while (!is_dead(philo->table) && philo->table->must_eat != philo->eat_count)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		ft_sleep(philo);
		if (!is_dead(philo->table)
			&& philo->table->must_eat != philo->eat_count)
			action_print(philo->table, philo->id, "is thinking");
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor_t;

	i = 0;
	table->start = get_time();
	while (i < table->philo_count)
	{
		pthread_create(&table->philos[i].thread, NULL,
			&routine, &table->philos[i]);
		pthread_mutex_lock(&table->meal_check);
		table->philos[i].last_eat = get_time();
		pthread_mutex_unlock(&table->meal_check);
		i++;
	}
	pthread_create(&monitor_t, NULL, monitor, table);
	pthread_join(monitor_t, NULL);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	free_all(table);
	return (0);
}
