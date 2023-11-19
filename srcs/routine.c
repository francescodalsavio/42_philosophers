/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:29:14 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/11/18 19:17:36 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	*monitor_philosopher(void *philosopher_data)
{
	t_philosopher	*philosopher;
	int				i;

	i = 0;
	philosopher = (t_philosopher *)philosopher_data;
	while (!philosopher->data->is_finished && !philosopher->data->dead)
	{
		i = 0;
		while (i < philosopher->data->number_of_philosophers)
		{
			if (philosopher->data->philosophers[i].eat_count < \
			philosopher->data->must_eat_count)
				break ;
			i++;
		}
		if (i == philosopher->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philosopher->data->lock);
			philosopher->data->is_finished = 1;
			ft_usleep(100);
			pthread_mutex_unlock(&philosopher->data->lock);
		}
	}
	return ((void *)0);
}

void	*check_dead_philosopher(void *philosopher_data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)philosopher_data;
	while (!philosopher->data->dead && !philosopher->data->is_finished)
	{
		pthread_mutex_lock(&philosopher->lock);
		if (get_current_time() >= \
		philosopher->time_to_die && philosopher->eating == 0)
		{
			pthread_mutex_unlock(&philosopher->lock);
			pthread_mutex_lock(&philosopher->data->lock);
			died(philosopher);
			philosopher->data->dead = 1;
			ft_usleep(10000);
			pthread_mutex_unlock(&philosopher->data->print);
			pthread_mutex_unlock(&philosopher->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philosopher->lock);
	}
	return ((void *)0);
}

void	*philosopher_routine(void *philosopher_data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)philosopher_data;
	philosopher->time_to_die = philosopher->data->time_to_die + \
	get_current_time();
	if (pthread_create(&philosopher->thread, NULL, \
	&check_dead_philosopher, (void *)philosopher))
		return ((void *)1);
	pthread_detach(philosopher->thread);
	while (philosopher->data->is_finished == 0 && philosopher->data->dead == 0)
	{
		eat(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return ((void *)0);
}

int	start(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = get_current_time();
	if (data->must_eat_count > 0)
	{
		if (pthread_create(&monitor_thread, NULL, &monitor_philosopher, \
		&data->philosophers[0]))
			return (handle_thread_error("Error creating monitor thread", data));
		pthread_detach(monitor_thread);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, &philosopher_routine, \
		&data->philosophers[i]))
			return (1);
		pthread_detach(data->threads[i]);
		ft_usleep(1);
		i++;
	}
	return (0);
}
