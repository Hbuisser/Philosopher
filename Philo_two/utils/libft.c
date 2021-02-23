  
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:33:37 by hbuisser          #+#    #+#             */
/*   Updated: 2021/02/22 20:45:04 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	prev;
	unsigned long long	digit;

	i = 0;
	prev = 0;
	digit = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		signe = (str[i++] == '-') ? -1 : 1;
	while (str[i] > 47 && str[i] < 58)
	{
		digit = digit * 10 + (str[i++] - '0');
		if (digit < prev || digit >= 9223372036854775807)
			return ((signe == -1) ? 0 : -1);
		prev = digit;
	}
	return (digit * signe);
}

static char	*ft_neg(int n)
{
	int		tmpn;
	int		len;
	char	*str;

	n *= -1;
	tmpn = n;
	len = 3;
	while (tmpn /= 10)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	str[0] = '-';
	return (str);
}

static char	*ft_zero(void)
{
	int		len;
	char	*str;

	len = 2;
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	int	tmpn;
	int	len;
	char*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_zero());
	if (n <= 0)
		return (ft_neg(n));
	tmpn = n;
	len = 2;
	while (tmpn /= 10)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

char		*ft_strjoin(char const *s1, char const *s2)
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
