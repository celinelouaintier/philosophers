/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-27 13:31:14 by clouaint          #+#    #+#             */
/*   Updated: 2024-11-27 13:31:14 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->table->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(&philo->table->forks[philo->id % philo->table->philo_count]);
	pthread_mutex_lock(&philo->table->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lld %d is eating\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	philo->last_eat = get_time();
	philo->eat_count++;
	usleep(philo->table->time_to_eat * 1000);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->philo_count]);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lld %d is sleeping\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->time_to_sleep * 1000);
}