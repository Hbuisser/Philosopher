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

int	print_str_eating(long int t, int phi)
{
	t_data	*values;

	t = 0;
	values = get_struct();
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)phi, 1);
	write(1, " is eating\n", 11);
	return (0);
}

int	print_str_sleeping(long int t, int phi)
{
	t_data	*values;

	t = 0;
	values = get_struct();
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)phi, 1);
	write(1, " is sleeping\n", 13);
	return (0);
}

int	print_str_thinking(long int t, int phi)
{
	t_data	*values;

	t = 0;
	values = get_struct();
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)phi, 1);
	write(1, " is thinking\n", 13);
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
	pthread_mutex_lock(&values->global_mutex);
	ft_putnbr_fd((long long)get_time(values), 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)i, 1);
	write(1, " died\n", 6);
	pthread_mutex_unlock(&values->dead_mutex);
	return (0);
}
