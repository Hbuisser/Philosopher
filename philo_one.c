/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/18 14:54:41 by hbuisser         ###   ########.fr       */
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

int create_join(t_data *values, int i)
{
	char *status;

	status = NULL;
	pthread_join(values->philo[i], (void *)&status);
	return (0);
}

int create_thread(t_data *values, int i)
{
	//print_array(values);
	printf("hello\n");
	pthread_create(&values->philo[i] , NULL, &routine, &values->iter);
	
	return (0);
}

int init_and_malloc_mutex_and_philo(t_data *values)
{
	int i;

	i = 0;
	values->mutex = malloc(sizeof(pthread_mutex_t) * values->nbr_of_philo);
	memset(values->mutex, 0, values->nbr_of_philo * 8);
	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_init(&values->mutex[i], NULL);
		i++;
	}
	values->philo = malloc(sizeof(pthread_t) * values->nbr_of_philo);
	memset(values->philo, 0, values->nbr_of_philo * 8);
	return (0);
}

int philo_in_action(t_data *values)
{
	int i;

	i = 0;
	//print_array(values);
	printf("avant init\n");
	init_and_malloc_mutex_and_philo(values);
	printf("apres init\n");
	while (i < values->nbr_of_philo)
	{
		create_thread(values, i);
		i++;
	}
	printf("apres create\n");
	//print_array(values);
	i = 0;
	while (i < values->nbr_of_philo)
	{
		create_join(values, i);
		i++;
	}
	printf("apres join\n");
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
	print_array(values);
	philo_in_action(values);
	//free_all(values);
	return (0);
}
