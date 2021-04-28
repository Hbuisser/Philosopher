/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 20:53:52 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	my_sleep(long int time, t_data *values)
{
	long int	i;
	long int	t;

	i = 0;
	t = get_time(values);
	//usleep(time * 0.8 * 1000);
	while (i < (time * 20))
	//while (1)
	{
		i++;
		if ((get_time(values) - t) >= time)
			break ;
		//usleep(500);
		usleep(50);
	}
}

long	get_time(t_data *values)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds - values->t_start);
}

int	complete_values2(t_data *values)
{
	int	i;

	i = -1;
	values->has_eat = (int *)malloc(sizeof(int) * values->nbr_of_philo);
	if (!values->has_eat)
		return (1);
	while (++i < values->nbr_of_philo)
		values->has_eat[i] = 0;
	i = -1;
	values->last_eat = (long int *)malloc(sizeof(long int)
			* values->nbr_of_philo);
	if (!values->last_eat)
		return (1);
	while (++i < values->nbr_of_philo)
		values->last_eat[i] = 0;
	return (0);
}

int	complete_values(t_data *values)
{
	int	i;

	values->iter = (int *)malloc(sizeof(int) * values->nbr_of_philo);
	if (!values->iter)
		return (1);
	i = -1;
	while (++i < values->nbr_of_philo)
		values->iter[i] = i;
	i = -1;
	values->count_eat = (int *)malloc(sizeof(int) * values->nbr_of_philo);
	if (!values->count_eat)
		return (1);
	while (++i < values->nbr_of_philo)
		values->count_eat[i] = 0;
	return (complete_values2(values));
}

int	parse_values(t_data *values, int argc, char **argv)
{
	values->nbr_of_philo = ft_atoi(argv[1]);
	values->time_to_die = ft_atoi(argv[2]);
	values->time_to_eat = ft_atoi(argv[3]);
	values->time_to_sleep = ft_atoi(argv[4]);
	if (values->nbr_of_philo < 2)
		return (1);
	if (values->time_to_die < 0)
		return (1);
	if (values->time_to_eat < 0)
		return (1);
	if (values->time_to_sleep < 0)
		return (1);
	if (argc == 6)
		values->nbr_of_time_each_philo_must_eat = ft_atoi(argv[5]);
	else
		values->nbr_of_time_each_philo_must_eat = 0;
	return (0);
}
