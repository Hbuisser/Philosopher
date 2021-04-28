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

void		ft_putnbr_fd(long long n, int fd)
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

int	print_str(long int t, int phi, char *mess)
{
	t_data	*values;

	t = 0;
	values = get_struct();
	//pthread_mutex_lock(&values->global_mutex);
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)phi, 1);
	write(1, mess, ft_strlen(mess));
	//pthread_mutex_unlock(&values->global_mutex);
	return (0);
}

int	print_str_fork(int i)
{
	t_data	*values;

	values = get_struct();
	pthread_mutex_lock(&values->global_mutex);
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)i, 1);
	write(1, " has taken a fork\n", 18);
	pthread_mutex_unlock(&values->global_mutex);
	return (0);
}

int	print_str_dead(int i)
{
	t_data	*values;

	values = get_struct();
	//pthread_mutex_lock(&values->global_mutex);
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)i, 1);
	write(1, " died\n", 6);
	//pthread_mutex_unlock(&values->dead_mutex);
	return (0);
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
