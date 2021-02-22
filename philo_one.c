/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 12:52:23 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int destroy_mutex(t_data *values)
{
	int i;

	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_unlock(&values->mutex[i]);
		pthread_mutex_destroy(&values->mutex[i]);
		i++;
	}
	return (0);
}

void lock_mutex()
{
	int i;
	t_data *values;

	values = get_struct();
	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_lock(&values->mutex[i]);
		i++;
	}
}

void *routine_time(void *arg)
{
	t_data *values;
	long int diff;
	int i;
	long int time;

	values = get_struct();
	while(values->status == -1)
	{
		i = 0;
		usleep(4000);
		while (i < values->nbr_of_philo)
		{
			diff = get_time() - values->last_eat[i];
			if (diff > values->time_to_die)
			{
			 	values->status = 1;
				time = get_time() - values->t_start;
				print_str_dead(i + 1, time);
				//printf("philo %d is dead %ld ms\n", i + 1, diff);
				lock_mutex();
				return (0);
			}
			i++;
		}
	}
	return (arg);
}

int thinking(t_data *values, int i)
{
	long int time;

	time = get_time() - values->t_start;
	if (values->status == -1)
		printf("%ld %d is thinking\n", time, i + 1);
	return (0);
}

int sleeping(t_data *values, int i)
{
	long int time;

	time = get_time() - values->t_start;
	if (values->status == -1)
	{
		printf("%ld %d is sleeping\n", time, i + 1);
		usleep(values->time_to_sleep * 1000);
	}
	return (0);
}

int eating(t_data *values, int i)
{
	long int time;

	time = get_time() - values->t_start;
	if (values->status == -1)
	{
		printf("%ld %d is eating\n", time, i + 1);
		values->last_eat[i] = get_time();
		usleep(values->time_to_eat * 1000);
	}
	return (0);
}

void *routine(void *arg)
{
	t_data *values;
	int fork;
	int next_fork;
	int i;
	long int time;

	values = get_struct();
	i = *(int *)arg;
	fork = i;
	next_fork = (i + 1) % values->nbr_of_philo;
	values->last_eat[i] = get_time();
	while (values->status == -1)
	{
		thinking(values, i);
		pthread_mutex_lock(&values->mutex[fork]);
		time = get_time() - values->t_start;
		printf("%ld %d has taken a fork\n", time, i + 1);
		pthread_mutex_lock(&values->mutex[next_fork]);
		//printf("%ld %d has taken a fork\n", time, i);
		eating(values, i);
		pthread_mutex_unlock(&values->mutex[fork]);
		pthread_mutex_unlock(&values->mutex[next_fork]);
		sleeping(values, i);
	}
	return (arg);
}

int init_and_malloc_mutex_and_thread(t_data *values)
{
	int i;

	i = 0;
	values->mutex = malloc(sizeof(pthread_mutex_t) * values->nbr_of_philo);
	memset(values->mutex, 0, values->nbr_of_philo * 8);
	values->thread = malloc(sizeof(pthread_t) * values->nbr_of_philo);
	memset(values->thread, 0, values->nbr_of_philo * 8);
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_init(&values->mutex[i], NULL);
		i++;
	}
	return (0);
}

int philo_in_action(t_data *values)
{
	int i;
	int *status;

	status = NULL;
	init_and_malloc_mutex_and_thread(values);
	values->t_start = get_time();
	pthread_create(&values->time, NULL, &routine_time, NULL);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_create(&values->thread[i] , NULL, &routine, &values->iter[i]);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_join(values->thread[i], (void *)&status);
	pthread_join(values->time, (void *)&status);
	destroy_mutex(values);
	return (0);
}

int main(int argc, char **argv) 
{
	t_data *values;
	int i;

	i = 0;
	values = get_struct();
	if (error_arg(argc, argv))
		return (0);
	if (init_struct(values))
		return (0);
	if (parse_values(values, argc, argv))
		return (0);
	if (complete_values(values))
		return (0);
	philo_in_action(values);
	//free_all(values);
	return (0);
}
