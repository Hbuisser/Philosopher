/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/17 19:51:04 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int sleeping(t_data *values, int i)
{
	printf("Philo %d dort\n", values->philo_num[i]);
	return (0);
}

int eating(t_data *values, int i)
{
	struct timeval temps_avant;
	struct timeval temps_apres;
	long int time;
	
	printf("Philo %d mange\n", values->philo_num[i]);
	gettimeofday (&temps_avant, NULL);
	usleep(values->time_to_eat);
	gettimeofday (&temps_apres, NULL);
	time = ((((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec) * 1000);
	printf("Philo %d a terminé de manger apres %ld ms\n", values->philo_num[i], time);
	return (0);
}

void *routine(void *arg)
{
	t_data *values;
	int i;
	int j;

	values = *get_struct();
	i = *(int *)arg;
	j = 0;
	while (j < values->nbr_of_philo)
	{
		printf("philonum: %d\n", values->philo_num[i]);
		j++;
	}
	// pthread_mutex_init(values->mutex[i], NULL);
	// if (values->mutex[i + 1])
	// 	pthread_mutex_init(values->mutex[i + 1], NULL);
		
	pthread_mutex_lock(values->mutex[i]);
	if (values->mutex[i + 1])
		pthread_mutex_lock(values->mutex[i + 1]);

	//eating(values, i);

	pthread_mutex_unlock(values->mutex[i]);
	if (values->mutex[i + 1])
		pthread_mutex_unlock(values->mutex[i + 1]);

	// pthread_mutex_destroy(values->mutex[i]);
	// if (values->mutex[i + 1])
	// 	pthread_mutex_destroy(values->mutex[i + 1]);

	//sleeping(values, i);
	
	return (arg);
}

int create_join(t_data *values, int i)
{
	char *status;

	status = NULL;
	pthread_join(*values->philo[i], (void *)&status);
	return (0);
}

int create_thread(t_data *values, int i)
{
	values->philo[i] = malloc(sizeof(pthread_t));
	pthread_create(values->philo[i] , NULL, &routine, &i);
	return (0);
}

int init_and_malloc_mutex(t_data *values)
{
	int i;

	i = 0;
	while (i < values->nbr_of_philo)
	{
		values->mutex[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(values->mutex[i], NULL);
		i++;
	}
	return (0);
}

int philo_in_action(t_data *values)
{
	int i;

	i = 0;
	init_and_malloc_mutex(values);
	while (i < values->nbr_of_philo)
	{
		create_thread(values, i);
		create_join(values, i);
		i++;
	}
	return (0);
}

int main(int argc, char **argv) 
{
	t_data *values;
	int i;

	i = 0;
	values = malloc(sizeof(t_data));
	values = *get_struct();
	printf("coucou\n");
	if (init_struct(values))
		return (0);
	printf("coucou\n");
	if (error_arg(argc, argv))
		return (0);
	if (parse_values(values, argc, argv))
	{
		write(2, "Wrong arguments\n", 16);
		return (0);
	}
	if (complete_values(values))
		return (0);
	philo_in_action(values);
	return (0);
}


// 	// struct timeval temps_avant;
// 	// struct timeval temps_apres;

// gettimeofday (&temps_avant, NULL);
//pthread_create(values->philo[i], NULL, &routine, &values->name[i]);
// gettimeofday (&temps_apres, NULL);
// printf("temps en us: %ld us\n", 
// 	(((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000
// 	+ temps_apres.tv_usec) - temps_avant.tv_usec) * 1000);



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
// 	while (i < values->nbr_of_philo)
// 	{
// 		values->philo[i] = malloc(sizeof(pthread_t));
// 		values->mutex[i] = malloc(sizeof(pthread_mutex_t));
// 		pthread_mutex_init(values->mutex[i], NULL);
// 		pthread_create(values->philo[i], NULL, &routine, &values->name[i]);
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