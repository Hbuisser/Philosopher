/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:16:31 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/02/17 19:42:37 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct      s_data
{
    int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_time_each_philo_must_eat;
    pthread_t **philo;
    pthread_mutex_t **mutex;
    int *fork;
    int *philo_num;
}                   t_data;

/*
*** Philo_one
*/

int philo_one(t_data *values);

/*
*** Utils
*/

int	ft_atoi(const char *str);
int only_digit(char *str);
int error_arg(int argc, char **argv);
t_data **get_struct(void);
int init_struct(t_data *values);
int parse_values(t_data *values, int argc, char **argv);
int complete_values(t_data *values);

#endif