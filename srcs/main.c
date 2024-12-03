/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:41:10 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/26 14:42:58 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philos(t_table *table)
{
    int i;

    printf("Nombre de philosophes : %d\n", table->philo_count);
    printf("Dead flag : %d\n", table->dead);

    for (i = 0; i < table->philo_count; i++)
	{
		printf("Philosophe %d\n", table->philos[i].id);
		printf("Nombre de repas : %d\n", table->philos[i].eat_count);
		printf("Dernier repas : %lld\n", table->philos[i].last_eat);
		printf("Thread : %ld\n", table->philos[i].thread);
		printf("T_to_die : %d\n", table->time_to_die);
		printf("T_to_eat : %d\n", table->time_to_eat);
		printf("T_to_sleep : %d\n", table->time_to_sleep);
		printf("Must_eat : %d\n", table->must_eat);
		printf("Start : %lld\n", table->start);
	}
}

void	free_all(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->meal_check);
	pthread_mutex_destroy(&table->dead_lock);
	free(table->forks);
	free(table->philos);
}

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
        return (printf("Error: wrong number of arguments\n"));
    if (init_all(ac, av, &table))
        return (printf("Error: initialization failed\n"));
	// else
	// 	print_philos(&table);
    if (start_simulation(&table))
	{
        return (printf("Error: simulation failed\n"));
		free_all(&table);
	}
    return (0);
}