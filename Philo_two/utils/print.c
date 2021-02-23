/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 10:54:59 by hbuisser         ###   ########.fr       */
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
	//pthread_mutex_lock(&values->global_mutex);
	write(1, str, ft_strlen(str));
	free(str);
	//pthread_mutex_unlock(&values->global_mutex);
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
	//pthread_mutex_lock(&values->global_mutex);
	write(1, str, ft_strlen(str));
	free(str);
	//pthread_mutex_unlock(&values->global_mutex);
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
	//pthread_mutex_lock(&values->global_mutex);
	write(1, str, ft_strlen(str));
	free(str);
	//pthread_mutex_unlock(&values->dead_mutex);
}