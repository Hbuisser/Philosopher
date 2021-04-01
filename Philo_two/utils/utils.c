/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 16:42:31 by hbuisser         ###   ########.fr       */
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

int	only_digit(char *str)
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

int	check_count_eat(void)
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
