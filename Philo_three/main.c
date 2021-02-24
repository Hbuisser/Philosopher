/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/24 20:36:02 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int		init_thread_and_sem(t_data *values)
{
	// values->thread = malloc(sizeof(pthread_t) * values->nbr_of_philo);
	// memset(values->thread, 0, values->nbr_of_philo * 8);
	sem_unlink("sem_forks");
	sem_unlink("sem_global");
	sem_unlink("sem_dead");
	values->sem_dead = sem_open("sem_dead", O_CREAT, 0660, 1);
	if (values->sem_dead == SEM_FAILED)
		return (1);
	values->sem_forks = sem_open("sem_forks", O_CREAT, 0660,
		values->nbr_of_philo);
	if (values->sem_forks == SEM_FAILED)
		return (1);
	values->sem_global = sem_open("sem_global", O_CREAT, 0660, 1);
	if (values->sem_global == SEM_FAILED)
		return (1);
	sem_wait(values->sem_dead);
	return (0);
}

int		philo_in_action(t_data *values)
{
	int	i;
	int	*status;

	if (init_thread_and_sem(values))
		return (0);
	status = NULL;
	i = 0;
	while (i < values->nbr_of_philo)
	{
		values->pid[i] = fork();
		values->philo = i + 1;
		if (values->pid[i] == 0)
		{
			//pthread_create(&values->thread, NULL, &routine, NULL);
			routine(values);
			pthread_create(&values->thread_time, NULL, &routine_time, NULL);
			//exit(0);
		}
		// printf("pid: %d\n", values->pid[i]);
		// printf("philo: %d\n", values->philo);
		// printf("=====\n");
		i++;
	}
	sem_wait(values->sem_dead);
	i = 0;
	while (i < values->nbr_of_philo)
	{
		//waitpid(values->pid[i], NULL, 0);
		i++;
	}
	return (0);
}

t_data	*get_struct(void)
{
	static t_data values;

	return (&values);
}

int		main(int argc, char **argv)
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
	philo_in_action(values);
	free_all(values);
	return (0);
}
