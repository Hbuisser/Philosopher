/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 12:48:30 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// char *print_str(long int t, int ph, )
// {
// 	char *time;
// 	char *philo;

// 	time = ft_itoa()
// 	return (str);
// }

char *print_str_dead(int i, long int diff)
{
	char *philo;
	char *time;
	char *str;
	char *mess;

	mess = ft_strdup(" died\n");
	philo = ft_itoa(i);
	time = ft_itoa((int)diff);
	str = ft_strjoin(time, " ");
	str = ft_strjoin(str, philo);
	str = ft_strjoin(str, mess);
	write(1, str, ft_strlen(str));
	free(str);
	return (str);
}

long    get_time(void)
{
    struct timeval  tp;
    long milliseconds;

    gettimeofday(&tp, NULL);
    milliseconds = tp.tv_sec * 1000;
    milliseconds += tp.tv_usec / 1000;
    return (milliseconds);
}

int print_array(t_data *values)
{
	int j;

	j = 0;
	while (j < values->nbr_of_philo)
	{
		printf("int: |%ld|\n", values->last_eat[j]);
		j++;
	}
	return(0);
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

t_data *get_struct(void)
{
	static t_data values;
	return (&values);
}

int check_time(t_data *values)
{
	int time_eat_sleep;

	time_eat_sleep = values->time_to_eat + values->time_to_sleep;
	if (values->time_to_die < values->time_to_eat ||
		values->time_to_die < values->time_to_sleep)
	{
		write(2, "Not enough time to die\n", 23);
		return (1);
	}
	if (values->time_to_die < time_eat_sleep)
	{
		write(2, "Not enough time to die\n", 23);
		return (1);
	}
	return (0);
}

int complete_values(t_data *values)
{
	int i;

	i = -1;
	if (!(values->iter = (int *)malloc(sizeof(int) * values->nbr_of_philo)))
		return (1);
	while (++i < values->nbr_of_philo)
		values->iter[i] = i;
	i = -1;
	if (!(values->philo_num = (int *)malloc(sizeof(int) * values->nbr_of_philo)))
		return (1);
	while (++i < values->nbr_of_philo)
		values->philo_num[i] = i + 1;
	i = -1;
	if (!(values->last_eat = (long int *)malloc(sizeof(long int) * values->nbr_of_philo)))
		return (1);
	while (++i < values->nbr_of_philo)
		values->last_eat[i] = 0;
	i = -1;
	while (++i < values->nbr_of_philo)
		values->philo_num[i] = i;
	return (0);
}

int parse_values(t_data *values, int argc, char **argv)
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
		values->nbr_of_time_each_philo_must_eat = 1;
	return (0);
}

int init_struct(t_data *values)
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
