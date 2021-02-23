/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:16:31 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/02/22 20:47:30 by hbuisser         ###   ########.fr       */
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
	int *count_eat;
	int *has_eat;
    int *iter;
    pthread_t *thread;
    pthread_t thread_time;
    pthread_mutex_t *mutex;
	pthread_mutex_t global_mutex;
	pthread_mutex_t dead_mutex;
    long int *last_eat;
    long int t_start;
    int status;
}                   t_data;

/*
*** Philo_one
*/

void *routine(void *arg);
void *routine_time(void *arg);
int check_count_eat(void);
t_data *get_struct(void);

/*
*** Utils
*/

int print_array(t_data *values);
int	ft_atoi(const char *str);
int only_digit(char *str);
int init_struct(t_data *values);
int parse_values(t_data *values, int argc, char **argv);
int complete_values(t_data *values);
long get_time(void);
void print_str_dead(int i, long int diff);
void print_str_fork(int i);
void print_str(long int t, int phi, char *mess);
void my_sleep(long int time);

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

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_free_all(char *s1, char *s2);

#endif