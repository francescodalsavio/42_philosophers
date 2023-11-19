/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:42:12 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/11/18 19:18:14 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].right_fork = &data->forks[i];
		if (i == 0)
			data->philosophers[i].left_fork = \
			&data->forks[data->number_of_philosophers - 1];
		else
			data->philosophers[i].left_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].data = data;
		data->philosophers[i].id = i + 1;
		data->philosophers[i].time_to_die = data->time_to_die;
		data->philosophers[i].eat_count = 0;
		data->philosophers[i].eating = 0;
		data->philosophers[i].status = 0;
		pthread_mutex_init(&data->philosophers[i].lock, NULL);
		i++;
	}
}

int	alloc_data(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->threads)
	{
		printf("error: threads malloc failed\n");
		return (1);
	}
	data->forks = \
	malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
	{
		printf("error: forks malloc failed\n");
		return (1);
	}
	data->philosophers = \
	malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!data->philosophers)
	{
		printf("error: philosophers malloc failed\n");
		return (1);
	}
	return (0);
}

int	init_general_structures(t_data *data, char **argv, int argc)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->number_of_philosophers < 1 || data->number_of_philosophers > 200) 
	{
		printf("error: the number of philosophers must be between 1 and 200\n");
		return (1);
	}
	if (data->time_to_die < 0 || data->time_to_eat < 0 \
	|| data->time_to_sleep < 0)
	{
		printf("error: time must be positive\n");
		return (1);
	}
	data->dead = 0;
	data->is_finished = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	if (init_general_structures(data, argv, argc))
		return (1);
	if (alloc_data(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philosophers(data);
	return (0);
}
