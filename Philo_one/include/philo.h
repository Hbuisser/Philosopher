/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:16:31 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/02/23 19:55:32 by hbuisser         ###   ########.fr       */
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

typedef struct s_data
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_time_each_philo_must_eat;
	pthread_t		*thread;
	pthread_t		thread_time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	global_mutex;
	pthread_mutex_t	dead_mutex;
	int				*count_eat;
	int				*has_eat;
	int				*iter;
	long int		*last_eat;
	long int		t_start;
	int				status;
}					t_data;

/*
*** Philo_one
*/

void				*routine(void *arg);
void				*routine_time(void *arg);
int					check_count_eat(void);
t_data				*get_struct(void);

/*
*** Utils
*/

int					print_array(t_data *values);
int					init_struct(t_data *values);
int					parse_values(t_data *values, int argc, char **argv);
int					complete_values(t_data *values);
long				get_time(t_data *values);
int					print_str_dead(int i);
int					print_str_fork(int i);
int					print_str_eating(long int t, int phi);
int					print_str_sleeping(long int t, int phi);
int					print_str_thinking(long int t, int phi);
void				my_sleep(long int time, t_data *values);
void				ft_putnbr_fd(long long n, int fd);

/*
*** Errors and Free
*/

int					only_digit(char *str);
int					error_arg(int argc, char **argv);
int					ft_free_str(char **str, int result);
int					free_all(t_data *values);
int					ft_free_int(int i, int result);
int					check_time(t_data *values);
char				*check_if_malloc(char *s1, char *s2);

/*
*** Libft
*/

char				*ft_itoa(int n);
long long			ft_atoi(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strjoin_free_all(char *s1, char *s2);

#endif
