/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/26 11:35:53 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*routine_time(void *arg)
{
	t_data	*values;

	values = get_struct();
	while (values->status == -1)
	{
		if ((get_time() - values->last_eat) > values->time_to_die)
		{
			values->status = 1;
			print_str_dead(values->philo, (get_time() - values->t_start));
			return (0);
		}
		usleep(3600);
	}
	return (arg);
}

int	thinking(t_data *values)
{
	long int	time;
	char		*mess;

	mess = ft_strdup(" is thinking\n");
	time = get_time() - values->t_start;
	if (values->status == -1)
		print_str(time, values->philo, mess);
	return (0);
}

int	sleeping(t_data *values)
{
	long int	time;
	char		*mess;

	time = get_time() - values->t_start;
	mess = ft_strdup(" is sleeping\n");
	if (values->status == -1)
	{
		print_str(time, values->philo, mess);
		my_sleep(values->time_to_sleep);
	}
	return (0);
}

int	eating(t_data *values)
{
	long int	time;
	char		*mess;

	values->count_eat += 1;
	mess = ft_strdup(" is eating\n");
	time = get_time() - values->t_start;
	if (values->status == -1)
	{
		values->last_eat = get_time();
		print_str(time, values->philo, mess);
		if (values->nbr_of_time_each_philo_must_eat > 0
			&& (values->count_eat >= values->nbr_of_time_each_philo_must_eat))
		{
			sem_post(values->sem_eat);
			values->status = 1;
		}
		my_sleep(values->time_to_eat);
	}
	return (1);
}

void	routine(t_data *values)
{
	values->last_eat = get_time();
	while (values->status == -1)
	{
		thinking(values);
		sem_wait(values->sem_forks);
		sem_wait(values->sem_forks);
		print_str_fork(values->philo);
		eating(values);
		sem_post(values->sem_forks);
		sem_post(values->sem_forks);
		if (values->status == 1)
			exit(0);
		sleeping(values);
	}
}
