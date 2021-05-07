/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 19:57:00 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	affiche(long long n, int fd)
{
	char	c;

	if (n > 9)
	{
		affiche((n / 10), fd);
		affiche((n % 10), fd);
	}
	else
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(long long n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			affiche(-n, fd);
		}
		else
			affiche(n, fd);
	}
}

int	init_struct(t_data *values)
{
	values->nbr_of_philo = 0;
	values->time_to_die = 0;
	values->time_to_eat = 0;
	values->time_to_sleep = 0;
	values->nbr_of_time_each_philo_must_eat = 0;
	values->t_start = 0;
	values->status = -1;
	return (0);
}

t_data	*get_struct(void)
{
	static t_data	values;

	return (&values);
}
