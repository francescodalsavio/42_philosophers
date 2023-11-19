/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:56 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/11/18 19:18:25 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosopher
{
	struct s_data	*data;
	pthread_t		thread;

	int				id;
	int				eat_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;	
}	t_philosopher;

typedef struct s_data
{
	int				number_of_philosophers;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				must_eat_count;

	u_int64_t		start_time;
	int				dead;
	int				is_finished;

	t_philosopher	*philosophers;
	pthread_t		*threads;

	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
}	t_data;

int			init_data(t_data *data, char **argv, int argc);
void		ft_exit(t_data *data);
int			are_args_integers(char **argv);
u_int64_t	get_current_time(void);
long		ft_atoi(const char *str);
int			handle_thread_error(char *str, t_data *data);
int			start(t_data *data);

void		eat(t_philosopher *philosopher);
int			ft_usleep(useconds_t time);
void		*philosopher_routine(void *philosopher_data);

void		sleeping(t_philosopher *philosopher);
void		thinking(t_philosopher *philosopher);
void		died(t_philosopher *philosopher);
