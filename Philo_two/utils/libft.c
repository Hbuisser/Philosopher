/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/23 19:45:01 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_long(int signe)
{
	if (signe == -1)
		return (0);
	else
		return (-1);
}

static int	ft_return(unsigned long long result, int signe)
{
	if (signe == -1 && (result - 1) == 9223372036854775807)
		return (result * signe);
	if (result > 9223372036854775807)
		return (ft_long(signe));
	return (result * signe);
}

long long	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	result;

	result = 0;
	signe = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (ft_return(result, signe));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_free_all(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (s2 == NULL || s1 == NULL)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(s1);
	free(s2);
	return (dest);
}
