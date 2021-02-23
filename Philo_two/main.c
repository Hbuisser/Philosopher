/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 12:15:54 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int		init_thread_and_sem(t_data *values)
{
	values->thread = malloc(sizeof(pthread_t) * values->nbr_of_philo);
	memset(values->thread, 0, values->nbr_of_philo * 8);
    //sem_init(&values->forks, 0, values->nbr_of_philo);
	values->forks_nbr = sem_open("forks_nbr", O_CREAT, 0600, values->nbr_of_philo);
	return (0);
}

int		philo_in_action(t_data *values)
{
	int	i;
	int	*status;

	status = NULL;
	init_thread_and_sem(values);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_create(&values->thread[i], NULL, &routine, &values->iter[i]);
	pthread_create(&values->thread_time, NULL, &routine_time, NULL);
	i = -1;
	while (++i < values->nbr_of_philo)
		pthread_join(values->thread[i], NULL);
	pthread_join(values->thread_time, NULL);
    sem_close(values->forks_nbr);
	return (0);
}

t_data *get_struct(void)
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
	return (0);
}