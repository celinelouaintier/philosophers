/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:31:14 by clouaint          #+#    #+#             */
/*   Updated: 2024/12/02 17:58:05 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	int first_fork;
    int second_fork;

	if (philo->table->dead)
    	return;
	first_fork = philo->id - 1;
	second_fork = philo->id % philo->table->philo_count;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->table->forks[second_fork]);
        pthread_mutex_lock(&philo->table->forks[first_fork]);
    }
    else
    {
        pthread_mutex_lock(&philo->table->forks[first_fork]);
        pthread_mutex_lock(&philo->table->forks[second_fork]);
    }
    action_print(philo->table, philo->id, "has taken a fork");
    action_print(philo->table, philo->id, "has taken a fork");
}

void	eat(t_philo *philo)
{
    if (philo->table->dead)
        return;
    action_print(philo->table, philo->id, "is eating");
    philo->last_eat = get_time();
    philo->eat_count++;
    precise_usleep(philo->table->time_to_eat, philo->table);
}

void	put_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->philo_count]);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->table->dead)
        return;
	action_print(philo->table, philo->id, "is sleeping");
	precise_usleep(philo->table->time_to_sleep, philo->table);
}