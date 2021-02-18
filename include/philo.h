/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:16:31 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/02/18 19:59:45 by hbuisser         ###   ########.fr       */
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
    int *philo_num;
    int *iter;
    int *clock_to_die;
    pthread_t *thread;
    pthread_t time;
    pthread_mutex_t *mutex;
}                   t_data;

/*
*** Philo_one
*/

int philo_one(t_data *values);

/*
*** Utils
*/

int print_array(t_data *values);
int	ft_atoi(const char *str);
int only_digit(char *str);
t_data *get_struct(void);
int init_struct(t_data *values);
int parse_values(t_data *values, int argc, char **argv);
int complete_values(t_data *values);

/*
*** Errors and Free
*/

int error_arg(int argc, char **argv);
int	ft_free_str(char **str, int result);
int free_all(t_data *values);
int ft_free_int(int i, int result);
int check_time(t_data *values);

#endif