/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/19 19:27:43 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int destroy_mutex(t_data *values)
{
	int i;

	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_destroy(&values->mutex[i]);
		i++;
	}
	return (0);
}

void *routine_time(void *arg)
{
	t_data *values;
	int status;
	long int t_check;
	long int diff;
	int i;

	i = 0;
	values = get_struct();
	status = -1;
	while(values->status == -1)
	{
		i = 0;
		while (i < values->nbr_of_philo)
		{
			usleep(5000);
			t_check = get_time();
			diff = t_check - values->last_eat[i];
			if (diff > values->time_to_die)
			{
			 	values->status = 1;
				printf("philo %d is dead ms\n", i);
				return (0);
			}
			i++;
		}
		//break ;
	}
	return (arg);
}

int thinking(t_data *values, int i)
{
	char time;

	i = 0;
	time = (char)get_time();
	values->nbr_of_time_each_philo_must_eat = 0;
	if (values->status == -1)
		printf("Philo %d pense\n", i + 1);
	return (0);
}

int sleeping(t_data *values, int i)
{
	struct timeval t_start;
	struct timeval t_end;
	long int t;

	if (values->status == -1)
		printf("Philo %d dort\n", i + 1);
	gettimeofday(&t_start, NULL);
	usleep(values->time_to_sleep * 1000);
	gettimeofday(&t_end, NULL);
	t = ((((t_end.tv_sec - t_start.tv_sec) * 1000000 + t_end.tv_usec) - t_start.tv_usec));
	if (values->status == -1)
		printf("Philo %d a terminé de dormir apres %ld ms\n", i + 1, t);
	return (0);
}

int eating(t_data *values, int i)
{
	struct timeval t_start;
	struct timeval t_end;
	long int t;
	
	if (values->status == -1)
		printf("Philo %d is eating\n", i + 1);
	gettimeofday(&t_start, NULL);
	values->last_eat[i] = get_time();
	usleep(values->time_to_eat * 1000);
	gettimeofday(&t_end, NULL);
	t = ((((t_end.tv_sec - t_end.tv_sec) * 1000000 + t_end.tv_usec) - t_start.tv_usec));
		if (values->status == -1)
	printf("Philo %d a terminé de manger apres %ld ms\n", i + 1, t);
	return (0);
}

void *routine(void *arg)
{
	t_data *values;
	int fork;
	int next_fork;

	values = get_struct();
	fork = *(int *)arg;
	next_fork = (fork + 1) % values->nbr_of_philo;
	values->last_eat[fork] = get_time();
	while (values->status == -1)
	{
		thinking(values, fork);
		pthread_mutex_lock(&values->mutex[fork]);
		pthread_mutex_lock(&values->mutex[next_fork]);
		eating(values, fork);
		pthread_mutex_unlock(&values->mutex[fork]);
		pthread_mutex_unlock(&values->mutex[next_fork]);
		sleeping(values, fork);
		//thinking(values, fork);
		//break ;
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
	values->t = get_time();
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
	// if (check_time(values))
	// 	return (0);
	philo_in_action(values);
	//free_all(values);
	return (0);
}
