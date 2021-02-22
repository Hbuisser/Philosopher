/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 17:55:31 by hbuisser         ###   ########.fr       */
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
	//pthread_mutex_unlock(&values->global_mutex);
	pthread_mutex_destroy(&values->global_mutex);
	return (0);
}

void unlock_mutex()
{
	int i;
	t_data *values;

	values = get_struct();
	pthread_mutex_unlock(&values->global_mutex);
	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_unlock(&values->mutex[i]);
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
	usleep(400);
	while(values->status == -1)
	{
		i = -1;
		while (++i < values->nbr_of_philo)
		{
			diff = get_time() - values->last_eat[i];
			if (diff > values->time_to_die)
			{
			 	values->status = 1;
				time = get_time() - values->t_start;
				//unlock_mutex();
				print_str_dead(i + 1, time);
				return (0);
			}
		}
		usleep(3600);
	}
	return (arg);
}

int thinking(t_data *values, int i)
{
	long int time;
	char *mess;

	mess = ft_strdup(" is thinking\n");
	time = get_time() - values->t_start;
	if (values->status == -1)
		print_str(time, i + 1, mess);
	return (0);
}

int sleeping(t_data *values, int i)
{
	long int time;
	char *mess;

	time = get_time() - values->t_start;
	mess = ft_strdup(" is sleeping\n");
	if (values->status == -1)
	{
		print_str(time, i + 1, mess);
		my_sleep(values->time_to_sleep);
	}
	return (0);
}

int eating(t_data *values, int i)
{
	long int time;
	char *mess;

	mess = ft_strdup(" is eating\n");
	time = get_time() - values->t_start;
	if (values->status == -1)
	{
		print_str(time, i + 1, mess);
		values->last_eat[i] = get_time();
		my_sleep(values->time_to_eat);
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
	char *mess;

	mess = ft_strdup(" has taken a fork\n");
	values = get_struct();
	i = *(int *)arg;
	fork = i;
	next_fork = (i + 1) % values->nbr_of_philo;
	if (i % 2 == 0)
	{
		next_fork = i;
		fork = (i + 1) % values->nbr_of_philo;
	}
	values->last_eat[i] = get_time();
	while (values->status == -1)
	{
		thinking(values, i);
		pthread_mutex_lock(&values->mutex[fork]);
		time = get_time() - values->t_start;
		print_str_fork(i + 1, time);
		//print_str(i + 1, time, mess);
		pthread_mutex_lock(&values->mutex[next_fork]);
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

	values->mutex = malloc(sizeof(pthread_mutex_t) * values->nbr_of_philo);
	memset(values->mutex, 0, values->nbr_of_philo * 8);
	values->thread = malloc(sizeof(pthread_t) * values->nbr_of_philo);
	memset(values->thread, 0, values->nbr_of_philo * 8);
	pthread_mutex_init(&values->global_mutex, NULL);
	pthread_mutex_init(&values->dead_mutex, NULL);
	pthread_mutex_lock(&values->dead_mutex);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_mutex_init(&values->mutex[i], NULL);
	return (0);
}

int philo_in_action(t_data *values)
{
	int i;
	int *status;

	status = NULL;
	init_and_malloc_mutex_and_thread(values);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_create(&values->thread[i], NULL, &routine, &values->iter[i]);
	pthread_create(&values->thread_time, NULL, &routine_time, NULL);
	// i = -1;
	// while (++i < values->nbr_of_philo)
	// 	pthread_join(values->thread[i], (void *)&status);
	// pthread_join(values->thread_time, (void *)&status);
	pthread_mutex_lock(&values->dead_mutex);
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
