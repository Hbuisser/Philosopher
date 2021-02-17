/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/01/31 14:39:00 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// void *routine(void *arg)
// {
// 	int i;
// 	t_data *values;

// 	values = get_struct();
// 	i = *(int *)arg;
// 	printf("i in routine: %d\n", i);
// 	printf("fork in routine: %d\n", values->fork[0]);
// 	while (1)
// 	{
// 		if (i != 0 && values->fork[i - 1] == 1)
// 		{
// 			values->fork[i - 1] = 0;
// 			pthread_mutex_lock(values->mutex[i - 1]);
// 			printf("is eating\n");
// 			sleep(values->time_to_eat);
// 			values->fork[i - 1] = 1;
// 			pthread_mutex_unlock(values->mutex[i - 1]);
// 			printf("is sleeping\n");
// 			sleep(values->time_to_sleep);
// 			break ;
// 		}
// 		// else
// 		// {
// 		// 	write(1, "is thinking\n", 12);
// 		// 	break ;	
// 		// }
// 		//printf("dead\n");
// 	}
// 	return (arg);
// }

// int philo_one(t_data *values)
// {
// 	int i;
// 	char *status;
// 	// struct timeval temps_avant;
// 	// struct timeval temps_apres;

// 	i = 0;
// 	status = NULL;
// 	values->philo = malloc(sizeof(pthread_t *));
// 	values->mutex = malloc(sizeof(pthread_mutex_t *));
// 	values->fork = (int *)malloc(sizeof(int) * values->nbr_of_philo);
// 	values->name = (int *)malloc(sizeof(int) * values->nbr_of_philo);
// 	while (i < values->nbr_of_philo)
// 	{
// 		values->fork[i] = 1;
// 		values->name[i] = i;
// 		i++;
// 	}
// 	i = 0;
// 	printf("fork: %d\n", values->fork[0]);
// 	while (i < values->nbr_of_philo)
// 	{
// 		values->philo[i] = malloc(sizeof(pthread_t));
// 		values->mutex[i] = malloc(sizeof(pthread_mutex_t));
// 		printf("i before: %d\n", i);
// 		pthread_mutex_init(values->mutex[i], NULL);
// 		// gettimeofday (&temps_avant, NULL);
// 		pthread_create(values->philo[i], NULL, &routine, &values->name[i]);
//     	// gettimeofday (&temps_apres, NULL);
//     	// printf("temps en us: %ld us\n", 
// 		// 	(((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000
// 		// 	+ temps_apres.tv_usec) - temps_avant.tv_usec) * 1000);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < values->nbr_of_philo)
// 	{
// 		pthread_join(*values->philo[i], (void *)&status);
// 		i++;
// 	}
// 	return(1);
// }

int create_thread(t_data *values)
{
	
	return (0);
}

int philo_in_action(t_data *values)
{
	//printf("hello%d\n", values->nbr_of_philo);
	create_thread(values);
	return (0);
}

int main(int argc, char **argv) 
{
	t_data *values;
	int i;

	i = 1;
	values = get_struct();
	init_struct(values);
	if (error_arg(argc, argv))
		return (0);
	if (parse_values(values, argc, argv))
		return (0);
	//philo_one(values);
	philo_in_action(values);
	return (0);
}
