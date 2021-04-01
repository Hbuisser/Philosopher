/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_init_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/25 12:41:51 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_arg(int argc, char **argv)
{
	int	i;

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

int	init_struct(t_data *values)
{
	values->nbr_of_philo = 0;
	values->time_to_die = 0;
	values->time_to_eat = 0;
	values->time_to_sleep = 0;
	values->nbr_of_time_each_philo_must_eat = 0;
	values->t_start = 0;
	values->status = -1;
	values->last_eat = 0;
	values->philo = 0;
	values->count_eat = 0;
	return (0);
}

int	free_all(t_data *values)
{
	free(values->has_eat);
	return (0);
}
