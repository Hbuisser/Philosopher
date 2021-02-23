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

void	my_sleep(long int time)
{
	long int	i;
	long int	t;

	i = 0;
	t = get_time();
	while (i < (time * 20))
	{
		i++;
		if ((get_time() - t) >= time)
			break ;
		usleep(50);
	}
}

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

int		only_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int		complete_values(t_data *values)
{
	int	i;

	if (!(values->iter = (int *)malloc(sizeof(int) * values->nbr_of_philo)))
		return (1);
	i = -1;
	while (++i < values->nbr_of_philo)
		values->iter[i] = i;
	i = -1;
	if (!(values->count_eat = (int *)malloc(sizeof(int) *
		values->nbr_of_philo)))
		return (1);
	while (++i < values->nbr_of_philo)
		values->count_eat[i] = 0;
	i = -1;
	if (!(values->has_eat = (int *)malloc(sizeof(int) * values->nbr_of_philo)))
		return (1);
	while (++i < values->nbr_of_philo)
		values->has_eat[i] = 0;
	i = -1;
	if (!(values->last_eat = (long int *)malloc(sizeof(long int) *
		values->nbr_of_philo)))
		return (1);
	while (++i < values->nbr_of_philo)
		values->last_eat[i] = 0;
	return (0);
}

int		parse_values(t_data *values, int argc, char **argv)
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
