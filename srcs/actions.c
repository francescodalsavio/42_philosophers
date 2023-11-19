/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:26:29 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/11/18 19:15:40 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d is died\n", get_current_time() - philo->data->start_time, \
	philo->id);
}

void	take_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->print);
	printf("%llu %d has taken a fork\n", get_current_time()
		- philosopher->data->start_time, philosopher->id);
	pthread_mutex_unlock(&philosopher->data->print);
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	take_fork(philo);
	pthread_mutex_lock(philo->right_fork);
	take_fork(philo);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
	philo->eat_count++;
	philo->eating = 1;
	philo->time_to_die = get_current_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d is eating\n", get_current_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->print);
	printf("%llu %d is sleeping\n", get_current_time()
		- philosopher->data->start_time, philosopher->id);
	pthread_mutex_unlock(&philosopher->data->print);
	ft_usleep(philosopher->data->time_to_sleep);
}

void	thinking(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->print);
	printf("%llu %d is thinking\n", get_current_time()
		- philosopher->data->start_time, philosopher->id);
	pthread_mutex_unlock(&philosopher->data->print);
}
