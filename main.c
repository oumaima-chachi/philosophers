/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:05:14 by ochachi           #+#    #+#             */
/*   Updated: 2025/07/28 16:09:58 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	validate_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [number_of_times_each_"
			"philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Invalid value for argument %d: '%s'\n",
				i, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread,
			NULL, philo_routine, &data->philos[i]);
		i++;
	}
}

static void	join_all_threads(t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (validate_arguments(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	init_philos(&data);
	create_philosopher_threads(&data);
	pthread_create(&monitor, NULL, death_monitor, &data);
	join_all_threads(&data, monitor);
	cleanup(&data);
	return (0);
}
