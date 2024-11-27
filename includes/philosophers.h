#ifndef PHILO_H
# define PHILO_H

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
    pthread_mutex_t	*forks;
    pthread_mutex_t	print;
    t_philo			*philos;
}					t_table;


int	init_all(int ac, char **av, t_table *table);
int	ft_atoi(const char *nptr);
int	get_time(void);


#endif