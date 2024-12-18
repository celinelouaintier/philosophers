/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-04 14:10:06 by clouaint          #+#    #+#             */
/*   Updated: 2024-12-04 14:10:06 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	long long		start;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philos;
}					t_table;

int			init_all(int ac, char **av, t_table *table);
int			ft_atoi(const char *nptr);
long long	get_time(void);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);
void		ft_sleep(t_philo *philo);
int			start_simulation(t_table *table);
void		precise_usleep(long long time_in_ms, t_table *table);
void		action_print(t_table *table, int id, char *string);
void		free_all(t_table *table);
int			is_dead(t_table *table);
int			has_eaten(t_philo *philo, int i);

#endif