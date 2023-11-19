/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:23:47 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/11/18 19:17:57 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	handle_thread_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

u_int64_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (handle_thread_error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

int	are_args_integers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
