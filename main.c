/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:24:42 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/11/18 19:17:47 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/philosophers.h"

void	clear_data(t_data	*data)
{
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosophers[i].lock);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (!are_args_integers(argv))
		return (1);
	if (init_data(&data, argv, argc))
		return (1);
	if (start(&data))
		return (1);
	while (!data.dead && !data.is_finished)
		;
	ft_exit(&data);
	return (0);
}
