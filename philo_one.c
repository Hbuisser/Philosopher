/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/18 16:30:01 by hbuisser         ###   ########.fr       */
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

int sleeping(t_data *values, int i)
{
	i = 0;
	//write(2, "Philo dort\n", 11);
	printf("Philo %d dort\n", values->philo_num[i]);
	usleep(values->time_to_sleep);
	return (0);
}

int eating(t_data *values, int i)
{
	struct timeval temps_avant;
	struct timeval temps_apres;
	long int time;
	
	printf("Philo %d mange\n", i + 1);
	gettimeofday (&temps_avant, NULL);
	usleep(values->time_to_eat);
	gettimeofday (&temps_apres, NULL);
	time = ((((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec) * 1000);
	printf("Philo %d a terminé de manger apres %ld ms\n", i + 1, time);
	return (0);
}

void *routine(void *arg)
{
	t_data *values;
	int i;

	values = get_struct();
	i = *(int *)arg;
	pthread_mutex_lock(&values->mutex[i]);
	if (&values->mutex[i + 1])
		pthread_mutex_lock(&values->mutex[i + 1]);
	eating(values, i);
	pthread_mutex_unlock(&values->mutex[i]);
	if (&values->mutex[i + 1])
		pthread_mutex_unlock(&values->mutex[i + 1]);
	sleeping(values, i);
	return (arg);
}

int init_and_malloc_mutex_and_philo(t_data *values)
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
	init_and_malloc_mutex_and_philo(values);
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
