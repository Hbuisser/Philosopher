/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/18 20:02:38 by hbuisser         ###   ########.fr       */
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
	int i;
	t_data *values;

	i = 0;
	values = get_struct();
	printf("time : %d\n", values->clock_to_die[i]);
	while (i < values->nbr_of_philo)
	{
		//
		i++;
	}
	return (arg);
}

int thinking(t_data *values, int i)
{
	values->nbr_of_time_each_philo_must_eat = 0;
	printf("Philo %d pense\n", i + 1);
	return (0);
}

int sleeping(t_data *values, int i)
{
	struct timeval temps_avant;
	struct timeval temps_apres;
	long int time;

	printf("Philo %d dort\n", i + 1);
	gettimeofday(&temps_avant, NULL);
	usleep(values->time_to_sleep);
	gettimeofday(&temps_apres, NULL);
	time = ((((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec));
	printf("Philo %d a terminé de dormir apres %ld ms\n", i + 1, time);
	return (0);
}

int eating(t_data *values, int i)
{
	struct timeval temps_avant;
	struct timeval temps_apres;
	long int time;
	
	//
	printf("Philo %d is eating\n", i + 1);
	gettimeofday(&temps_avant, NULL);
	values->clock_to_die[i] = temps_avant.tv_usec * 1000000 + temps_avant.tv_usec;
	printf("time : %d\n", values->clock_to_die[i]);
	usleep(values->time_to_eat);
	gettimeofday(&temps_apres, NULL);
	time = ((((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec));
	printf("Philo %d a terminé de manger apres %ld ms\n", i + 1, time);
	return (0);
}

void *routine(void *arg)
{
	t_data *values;
	int fork;
	int next_fork;
	struct timeval t_avant;
	struct timeval t_apres;
	long int time;

	values = get_struct();
	fork = *(int *)arg;
	next_fork = (fork + 1) % values->nbr_of_philo;
	time = ((((t_apres.tv_sec - t_avant.tv_sec) * 1000000 + t_apres.tv_usec) - t_avant.tv_usec) * 1000);
	while (1)
	{
		pthread_mutex_lock(&values->mutex[fork]);
		pthread_mutex_lock(&values->mutex[next_fork]);
		eating(values, fork);
		pthread_mutex_unlock(&values->mutex[fork]);
		pthread_mutex_unlock(&values->mutex[next_fork]);
		sleeping(values, fork);
		thinking(values, fork);
		break ;
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
	i = 0;
	init_and_malloc_mutex_and_thread(values);
	pthread_create(&values->time, NULL, &routine_time, NULL);
	while (i < values->nbr_of_philo)
	{
		pthread_create(&values->thread[i] , NULL, &routine, &values->iter[i]);
		i++;
	}
	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_join(values->thread[i], (void *)&status);
		i++;
	}
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
