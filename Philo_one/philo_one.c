/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/03/02 14:51:20 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*routine_time(void *arg)
{
	t_data		*values;
	int			i;

	values = get_struct();
	while (values->status == -1)
	{
		i = -1;
		while (++i < values->nbr_of_philo)
		{
			if ((get_time(values) - values->last_eat[i]) > values->time_to_die)
			{
				values->status = 1;
				print_str_dead(i + 1);
				return (0);
			}
		}
		if (check_count_eat() > 0)
		{
			pthread_mutex_lock(&values->global_mutex);
			values->status = 1;
			pthread_mutex_unlock(&values->dead_mutex);
		}
		usleep(2000);
	}
	return (arg);
}

int	thinking(t_data *values, int i)
{
	long int	time;

	time = get_time(values);
	if (values->status == -1)
	{
		pthread_mutex_lock(&values->global_mutex);
		print_str_thinking(time, i + 1);
		pthread_mutex_unlock(&values->global_mutex);
	}
	return (0);
}

int	sleeping(t_data *values, int i)
{
	long int	time;

	time = get_time(values);
	if (values->status == -1)
	{
		pthread_mutex_lock(&values->global_mutex);
		print_str_sleeping(time, i + 1);
		pthread_mutex_unlock(&values->global_mutex);
		my_sleep(values->time_to_sleep, values);
	}
	return (0);
}

int	eating(t_data *values, int i, int fork, int next_fork)
{
	long int	time;

	pthread_mutex_lock(&values->mutex[fork]);
	pthread_mutex_lock(&values->mutex[next_fork]);
	print_str_fork(i + 1);
	print_str_fork(i + 1);
	pthread_mutex_lock(&values->global_mutex);
	pthread_mutex_unlock(&values->global_mutex);
	time = get_time(values);
	if (values->status == -1)
	{
		values->count_eat[i] += 1;
		pthread_mutex_lock(&values->global_mutex);
		print_str_eating(time, i + 1);
		pthread_mutex_unlock(&values->global_mutex);
		values->last_eat[i] = get_time(values);
		my_sleep(values->time_to_eat, values);
	}
	pthread_mutex_unlock(&values->mutex[fork]);
	pthread_mutex_unlock(&values->mutex[next_fork]);
	return (0);
}

void	*routine(void *arg)
{
	t_data		*values;
	int			fork;
	int			next_fork;
	int			i;

	values = get_struct();
	i = *(int *)arg;
	fork = i;
	next_fork = (fork + 1) % values->nbr_of_philo;
	if (i % 2 == 0)
	{
		next_fork = i;
		fork = (next_fork + 1) % values->nbr_of_philo;
		usleep(500);
	}
	values->last_eat[i] = get_time(values);
	pthread_detach(*values->thread);
	while (values->status == -1)
	{
		thinking(values, i);
		eating(values, i, fork, next_fork);
		sleeping(values, i);
	}
	return (0);
}
