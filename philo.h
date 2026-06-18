/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:02:40 by ochachi           #+#    #+#             */
/*   Updated: 2025/07/28 13:13:50 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long long			num_philos;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					must_eat_count;
	bool				someone_died;
	bool				done_eating;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	long long			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

long					ft_atoi(const char *str);
int						ft_isdigit(int c);
long long				get_time(void);
void					print_status(t_data *data, int id, char *status);
bool					check_death(t_data *data);
void					*death_monitor(void *arg);
void					*philo_routine(void *arg);
void					eat(t_philo *philo);
int						init_data(t_data *data, int argc, char **argv);
void					init_philos(t_data *data);
void					cleanup(t_data *data);
void					take_forks(t_philo *philo);
void					release_forks(t_philo *philo);
void					deeeed(t_philo *philo, bool *dead, bool *done_eating);

#endif