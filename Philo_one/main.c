/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 20:57:15 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int		check_count_eat(void)
{
	int		i;
	t_data	*values;

	values = get_struct();
	i = 0;
	while (i < values->nbr_of_philo)
	{
		if (values->count_eat[i] == values->nbr_of_time_each_philo_must_eat)
			values->has_eat[i] = 1;
		i++;
	}
	i = 0;
	while (i < values->nbr_of_philo)
	{
		if (values->has_eat[i] == 0)
			return (-1);
		i++;
	}
	if (values->nbr_of_time_each_philo_must_eat > 0)
		return (1);
	return (0);
}

int		destroy_mutex(t_data *values)
{
	int		i;

	i = 0;
	while (i < values->nbr_of_philo)
	{
		pthread_mutex_destroy(&values->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&values->global_mutex);
	pthread_mutex_destroy(&values->dead_mutex);
	return (0);
}

int		init_and_malloc_mutex_and_thread(t_data *values)
{
	int		i;

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

int		philo_in_action(t_data *values)
{
	int	i;
	int	*status;

	status = NULL;
	init_and_malloc_mutex_and_thread(values);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_create(&values->thread[i], NULL, &routine, &values->iter[i]);
	pthread_create(&values->thread_time, NULL, &routine_time, NULL);
	pthread_mutex_lock(&values->dead_mutex);
	destroy_mutex(values);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	*values;
	int		i;

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
	values->t_start = get_time();
	philo_in_action(values);
	return (0);
}
