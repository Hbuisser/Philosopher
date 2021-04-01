/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:16:31 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/02/23 19:49:25 by hbuisser         ###   ########.fr       */
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
# include <semaphore.h>

typedef struct s_data
{
	int			nbr_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_of_time_each_philo_must_eat;
	long int	t_start;
	int			*count_eat;
	int			*has_eat;
	int			*iter;
	pthread_t	*thread;
	pthread_t	thread_time;
	sem_t		*sem_forks;
	sem_t		*sem_global;
	sem_t		*sem_dead;
	long int	*last_eat;
	int			status;
}				t_data;

/*
*** Philo_two and main
*/

void			*routine(void *arg);
void			*routine_time(void *arg);
t_data			*get_struct(void);
int				eating(t_data *values, int i);
int				sleeping(t_data *values, int i);
int				thinking(t_data *values, int i);

/*
*** Utils
*/

int				check_count_eat(void);
int				only_digit(char *str);
int				parse_values(t_data *values, int argc, char **argv);
int				complete_values(t_data *values);
long			get_time(void);
void			my_sleep(long int time);
int				check_time(t_data *values);

/*
*** Print
*/

void			print_str_dead(int i, long int diff);
void			print_str_fork(int i);
void			print_str(long int t, int phi, char *mess);

/*
*** Errors, init and free
*/

int				error_arg(int argc, char **argv);
int				init_struct(t_data *values);
int				free_all(t_data *values);

/*
*** Libft
*/

long long		ft_atoi(const char *str);
char			*ft_itoa(int n);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strjoin_free_all(char *s1, char *s2);

#endif
