/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/17 18:05:51 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int init_struct(t_data *values)
{
	int i;

	i = 0;
    values->nbr_of_philo = 0;
	values->time_to_die = 0;
	values->time_to_eat = 0;
	values->time_to_sleep = 0;
    values->nbr_of_time_each_philo_must_eat = 0;
	if (!(values->philo = malloc(sizeof(pthread_t *))))
		return (1);
	if (!(values->mutex = malloc(sizeof(pthread_mutex_t *))))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	prev;
	unsigned long long	digit;

	i = 0;
	prev = 0;
	digit = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		signe = (str[i++] == '-') ? -1 : 1;
	while (str[i] > 47 && str[i] < 58)
	{
		digit = digit * 10 + (str[i++] - '0');
		if (digit < prev || digit >= 9223372036854775807)
			return ((signe == -1) ? 0 : -1);
		prev = digit;
	}
	return (digit * signe);
}

int only_digit(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int error_arg(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5)
	{
		write(2, "Not enough arguments\n", 21);
		return (1);
	}
	else if (argc > 6)
	{
		write(2, "Too many arguments\n", 19);
		return (1);
	}
	while (i < argc)
	{
		if (!only_digit(argv[i]))
		{
			write(2, "Invalid argument\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}

t_data *get_struct(void)
{
	static t_data values;
	return (&values);
}

int parse_values(t_data *values, int argc, char **argv)
{
	values->nbr_of_philo = ft_atoi(argv[1]);
	values->time_to_die = ft_atoi(argv[2]);
	values->time_to_eat = ft_atoi(argv[3]);
	values->time_to_sleep = ft_atoi(argv[4]);
	if (values->nbr_of_philo < 0)
		return (1);
	if (values->time_to_die < 0)
		return (1);
	if (values->time_to_eat < 0)
		return (1);
	if (values->time_to_sleep < 0)
		return (1);
	if (values->nbr_of_philo < 2)
	{
		write(1, "Not enough philosopher\n", 24);
		return (1);
	}
	if (argc == 6)
		values->nbr_of_time_each_philo_must_eat = ft_atoi(argv[5]);
	else
		values->nbr_of_time_each_philo_must_eat = 1;
	return (0);
}

int complete_values(t_data *values)
{
	int i;

	i = 0;
	if (!(values->fork = (int *)malloc(sizeof(int) * values->nbr_of_philo)))
		return (1);
	if (!(values->philo_num = (int *)malloc(sizeof(int) * values->nbr_of_philo)))
		return (1);
	while (i < values->nbr_of_philo)
	{
		values->fork[i] = 1;
		values->philo_num[i] = i;
		i++;
	}
	return (0);
}