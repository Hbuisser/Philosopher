/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/18 13:27:28 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int free_all(t_data *values)
// {
//     int i;

// 	i = 0;
// 	while (i < values->nbr_of_philo)
// 	{
// 		ft_free_int(values->philo_num[i], 0);
// 		i++;
// 	}
// 	free(values->philo);
// 	free(values->mutex);
// 	return (0);
// }

int		ft_free_str(char **str, int result)
{
	if (*str)
	{
		free(*str);
		*str = 0;
	}
	return (result);
}

// int 	ft_free_int(int i, int result)
// {
// 	if (i)
// 	{
// 		free((void *)i);
// 		i = 0;
// 	}
// 	return (result);
// }