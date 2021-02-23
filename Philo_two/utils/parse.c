/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 10:38:22 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
