/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:29:30 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/02 17:59:15 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].last_eat = 0;
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

static void init_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->meal_check, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

static int	init_table(t_table *table, int ac, char **av)
{
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->must_eat = -1;
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	table->dead = 0;
	table->start = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return (1);
	init_mutex(table);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (1);
	init_philos(table);
	return (0);
}

int	init_all(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (atoi(av[1]) < 2 || atoi(av[1]) > 200)
		return (1);
	if (atoi(av[2]) < 60 || atoi(av[3]) < 60 || atoi(av[4]) < 60)
		return (1);
	if (ac == 6 && atoi(av[5]) < 1)
		return (1);
	if (init_table(table, ac, av))
		return (1);
	return (0);
}
