/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:05:00 by ochachi           #+#    #+#             */
/*   Updated: 2025/07/28 15:31:47 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_status(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_status(philo->data, philo->id, "has taken a fork");
}

static void	handle_one_philo(t_philo *philo)
{	
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->data, philo->id, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		handle_one_philo(philo);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		release_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo->data, philo->id, "is eating");
	if (philo->data->time_to_eat > philo->data->time_to_die)
		usleep(philo->data->time_to_die * 1000);
	else
		usleep(philo->data->time_to_eat * 1000);
	release_forks(philo);
}

static int	philo_think_and_sleep(t_philo *philo, bool *dead, bool *done_eating)
{
	print_status(philo->data, philo->id, "is sleeping");
	if (philo->data->time_to_sleep > philo->data->time_to_die)
		usleep(philo->data->time_to_die * 1000);
	else
		usleep(philo->data->time_to_sleep * 1000);
	deeeed(philo, dead, done_eating);
	if (*dead || *done_eating)
		return (1);
	print_status(philo->data, philo->id, "is thinking");
	if (philo->data->num_philos % 2 != 0)
	{
		if (philo->data->time_to_eat < philo->data->time_to_sleep)
			usleep(1);
		else
			usleep(philo->data->time_to_eat * 1000);
	}
	deeeed(philo, dead, done_eating);
	if (*dead || *done_eating)
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	bool	dead;
	bool	done_eating;

	philo = (t_philo *)arg;
	dead = false;
	done_eating = false;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		deeeed(philo, &dead, &done_eating);
		if (dead || done_eating)
			break ;
		eat(philo);
		deeeed(philo, &dead, &done_eating);
		if (dead || done_eating)
			break ;
		if (philo_think_and_sleep(philo, &dead, &done_eating))
			break ;
	}
	return (NULL);
}
