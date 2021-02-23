/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 19:56:28 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_arg(int argc, char **argv)
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

int	free_all(t_data *values)
{
	int i;

	i = 0;
	free(values->count_eat);
	free(values->has_eat);
	free(values->iter);
	free(values->last_eat);
	return (0);
}
