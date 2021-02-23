/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 14:28:11 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int		init_thread_and_sem(t_data *values)
{
	values->thread = malloc(sizeof(pthread_t) * values->nbr_of_philo);
	memset(values->thread, 0, values->nbr_of_philo * 8);
	sem_unlink("sem_forks");
	sem_unlink("sem_global");
	sem_unlink("sem_dead");
	values->sem_forks = sem_open("sem_forks", O_CREAT, 0660, values->nbr_of_philo);
	values->sem_global = sem_open("sem_global", O_CREAT, 0660, 1);
	values->sem_dead = sem_open("sem_dead", O_CREAT, 0660, 1);
	if (values->sem_forks == SEM_FAILED)
		printf("error in sem open\n");
	//sem_wait(values->sem_dead);
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
	
	//sem_wait(values->sem_dead);
    sem_close(values->sem_forks);
	sem_close(values->sem_global);
	sem_close(values->sem_dead);
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

// Une implémentation des sémaphores se compose en général de quatre fonctions :

// une fonction d'initialisation qui permet de créer le sémaphore et de lui attribuer une valeur initiale nulle ou positive.
// une fonction permettant de détruire un sémaphore et de libérer les ressources qui lui sont associées.
// une fonction post qui est utilisée par les threads pour modifier la valeur du sémaphore. 
// 	S'il n'y a pas de thread en attente dans la queue associée au sémaphore, sa valeur est incrémentée d'une unité. 
// 	Sinon, un des threads en attente est libéré et passe à l'état Ready.
// une fonction wait qui est utilisée par les threads pour tester la valeur d'un sémaphore. 
// 	Si la valeur du sémaphore est positive, elle est décrémentée d'une unité et la fonction réussit. 
// 	Si le sémaphore a une valeur nulle, le thread est bloqué jusqu'à ce qu'un autre thread le débloque en appelant la fonction post.