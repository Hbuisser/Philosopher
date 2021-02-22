/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:16:31 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/02/22 12:36:08 by hbuisser         ###   ########.fr       */
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
    pthread_t *thread;
    pthread_t time;
    pthread_mutex_t *mutex;
    long int *last_eat;
    long int t_start;
    int status;
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
long    get_time(void);
char *print_str_dead(int i, long int diff);

/*
*** Errors and Free
*/

int error_arg(int argc, char **argv);
int	ft_free_str(char **str, int result);
int free_all(t_data *values);
int ft_free_int(int i, int result);
int check_time(t_data *values);

/*
*** Libft
*/

char		*ft_itoa(int n);
int			ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

#endif