/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/26 11:40:59 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	init_sem(t_data *values)
{
	sem_unlink("sem_eat");
	values->sem_eat = sem_open("sem_eat", O_CREAT, 0660, values->nbr_of_philo);
	if (values->sem_eat == SEM_FAILED)
		return (1);
	sem_unlink("sem_forks");
	values->sem_forks = sem_open("sem_forks",
			O_CREAT, 0660, values->nbr_of_philo);
	if (values->sem_forks == SEM_FAILED)
		return (1);
	sem_unlink("sem_global");
	values->sem_global = sem_open("sem_global", O_CREAT, 0660, 1);
	if (values->sem_global == SEM_FAILED)
		return (1);
	return (0);
}

int	philo_in_action(t_data *values)
{
	int	i;

	if (init_sem(values))
		return (1);
	i = -1;
	while (++i < values->nbr_of_philo)
		sem_wait(values->sem_eat);
	i = 0;
	while (i < values->nbr_of_philo)
	{
		values->pid[i] = fork();
		values->philo = i + 1;
		if (values->pid[i] == 0)
		{
			pthread_create(&values->thread_time, NULL, &routine_time, NULL);
			routine(values);
		}
		i++;
	}
	i = -1;
	while (++i < values->nbr_of_philo)
		sem_wait(values->sem_eat);
	return (0);
}

t_data	*get_struct(void)
{
	static t_data	values;

	return (&values);
}

int	main(int argc, char **argv)
{
	t_data	*values;
	int		i;

	i = 0;
	values = get_struct();
	if (error_arg(argc, argv))
		return (0);
	if (init_struct(values))
		return (0);
	if (parse_values(values, argc, argv))
		return (0);
	if (complete_values(values))
		return (0);
	values->t_start = get_time();
	if (philo_in_action(values))
		return (0);
	free_all(values);
	return (0);
}
