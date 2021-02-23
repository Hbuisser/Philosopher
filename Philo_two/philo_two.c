/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 12:16:55 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*routine_time(void *arg)
{
	t_data		*values;
	int			i;

	values = get_struct();
	while (values->status == -1)
	{
		i = -1;
		while (++i < values->nbr_of_philo)
		{
			if ((get_time() - values->last_eat[i]) > values->time_to_die)
			{
				values->status = 1;
				print_str_dead(i + 1, (get_time() - values->t_start));
				return (0);
			}
		}
		// if (check_count_eat() > 0)
		// {
		// 	// pthread_mutex_lock(&values->global_mutex);
		// 	values->status = 1;
		// 	// pthread_mutex_unlock(&values->dead_mutex);
		// }
		usleep(3600);
	}
	return (arg);
}

int		thinking(t_data *values, int i)
{
	long int	time;
	char		*mess;

	mess = ft_strdup(" is thinking\n");
	time = get_time() - values->t_start;
	if (values->status == -1)
		print_str(time, i + 1, mess);
	return (0);
}

int		sleeping(t_data *values, int i)
{
	long int	time;
	char		*mess;

	time = get_time() - values->t_start;
	mess = ft_strdup(" is sleeping\n");
	if (values->status == -1)
	{
		print_str(time, i + 1, mess);
		my_sleep(values->time_to_sleep);
	}
	return (0);
}

int		eating(t_data *values, int i)
{
	long int	time;
	char		*mess;

	values->count_eat[i] += 1;
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

void	*routine(void *arg)
{
	t_data		*values;
	// int			fork;
	// int			next_fork;
	int			i;

	values = get_struct();
	i = *(int *)arg;
	// fork = i;
	// next_fork = (i + 1) % values->nbr_of_philo;
	// if (i % 2 == 0)
	// {
	// 	next_fork = i;
	// 	fork = (i + 1) % values->nbr_of_philo;
	// }
	values->last_eat[i] = get_time();
	while (values->status == -1)
	{
		thinking(values, i);
        sem_wait(values->forks_nbr);
		//pthread_mutex_lock(&values->mutex[fork]);
		print_str_fork(i + 1);
        sem_wait(values->forks_nbr);
		//pthread_mutex_lock(&values->mutex[next_fork]);
		eating(values, i);
        sem_post(values->forks_nbr);
        sem_post(values->forks_nbr);
		//pthread_mutex_unlock(&values->mutex[fork]);
		//pthread_mutex_unlock(&values->mutex[next_fork]);
		sleeping(values, i);
	}
	return (0);
}
