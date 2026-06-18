/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:14:09 by ochachi           #+#    #+#             */
/*   Updated: 2025/07/23 06:05:27 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_data *data)
{
	bool	died;

	pthread_mutex_lock(&data->death_mutex);
	if (data->done_eating || data->someone_died)
		died = true;
	else
		died = false;
	pthread_mutex_unlock(&data->death_mutex);
	return (died);
}

long	get_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (last_meal);
}

int	get_eat_count(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->data->meal_mutex);
	count = philo->eat_count;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (count);
}

static int	cheeeeck_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (get_time() - get_last_meal(&data->philos[i])
			>= data->time_to_die)
		{
			print_status(data, i + 1, "died");
			pthread_mutex_lock(&data->death_mutex);
			if (!data->someone_died)
			{
				data->someone_died = true;
				pthread_mutex_unlock(&data->death_mutex);
			}
			else
				pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->someone_died && !data->done_eating)
	{
		if (cheeeeck_death(data))
			return (NULL);
		i = 0;
		pthread_mutex_lock(&data->meal_mutex);
		while (data->must_eat_count != -1
			&& i < data->num_philos
			&& data->philos[i].eat_count >= data->must_eat_count)
			i++;
		pthread_mutex_unlock(&data->meal_mutex);
		if (i == data->num_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->done_eating = true;
			pthread_mutex_unlock(&data->death_mutex);
		}
		usleep(50);
	}
	return (NULL);
}
