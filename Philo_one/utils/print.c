/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 20:56:29 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_str(long int t, int phi, char *mess)
{
	char	*time;
	char	*philo;
	char	*str;
	t_data	*values;

	values = get_struct();
	time = ft_itoa((int)t);
	philo = ft_itoa(phi);
	str = ft_strjoin_free(time, " ");
	str = ft_strjoin_free_all(str, philo);
	str = ft_strjoin_free_all(str, mess);
	pthread_mutex_lock(&values->global_mutex);
	write(1, str, ft_strlen(str));
	free(str);
	pthread_mutex_unlock(&values->global_mutex);
}

void	print_str_fork(int i)
{
	char	*philo;
	char	*time;
	char	*str;
	char	*mess;
	t_data	*values;

	values = get_struct();
	time = ft_itoa((int)(get_time() - values->t_start));
	mess = ft_strdup(" has taken a fork\n");
	philo = ft_itoa(i);
	str = ft_strjoin(time, " ");
	str = ft_strjoin_free_all(str, philo);
	str = ft_strjoin_free_all(str, mess);
	pthread_mutex_lock(&values->global_mutex);
	write(1, str, ft_strlen(str));
	free(str);
	pthread_mutex_unlock(&values->global_mutex);
}

void	print_str_dead(int i, long int diff)
{
	char	*philo;
	char	*time;
	char	*str;
	char	*mess;
	t_data	*values;

	values = get_struct();
	mess = ft_strdup(" died\n");
	philo = ft_itoa(i);
	time = ft_itoa((int)diff);
	str = ft_strjoin(time, " ");
	str = ft_strjoin_free_all(str, philo);
	str = ft_strjoin_free_all(str, mess);
	pthread_mutex_lock(&values->global_mutex);
	write(1, str, ft_strlen(str));
	free(str);
	pthread_mutex_unlock(&values->dead_mutex);
}

int		init_struct(t_data *values)
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

t_data *get_struct(void)
{
	static t_data values;
	return (&values);
}
