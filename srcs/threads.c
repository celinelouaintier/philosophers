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
            pthread_mutex_lock(&table->dead_lock);
            if (get_time() - table->philos[i].last_eat > table->time_to_die)
            {
				action_print(table, table->philos[i].id, "died");
                table->dead = 1;
                pthread_mutex_unlock(&table->dead_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&table->dead_lock);
            i++;
        }
        usleep(500);
    }
    return NULL;
}

void	*routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2)
        usleep(15000);
    while (!philo->table->dead && philo->table->must_eat != philo->eat_count)
    {
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        ft_sleep(philo);
        if (!philo->table->dead)
            action_print(philo->table, philo->id, "is thinking");
    }
    return (NULL);
}

int	start_simulation(t_table *table)
{
    int			i;
    pthread_t	monitor_t;
    int			ret;

    i = 0;
	table->start = get_time();
    while (i < table->philo_count)
    {
        ret = pthread_create(&table->philos[i].thread, NULL, &routine, &table->philos[i]);
        if (ret != 0)
            return (1);
		table->philos[i].last_eat = get_time();
        i++;
    }
    ret = pthread_create(&monitor_t, NULL, monitor, table);
    if (ret != 0)
        return (1);
    ret = pthread_join(monitor_t, NULL);
    i = 0;
    while (i < table->philo_count)
    {
        ret = pthread_join(table->philos[i].thread, NULL);
        i++;
    }
    return (0);
}
