/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:52:53 by emichels          #+#    #+#             */
/*   Updated: 2023/11/16 09:34:57 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int c)
{
	size_t	len;
	long	mod;

	if (c == 0)
		return (1);
	if (c < 10)
		len = 1;
	else
		len = 0;
	mod = 10;
	while (c % mod != c)
	{
		mod *= 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_putnbr(char *str, unsigned int n)
{
	size_t	i;

	i = 0;
	if (n < 10)
	{
		while (str[i])
			i++;
		str[i] = n + '0';
	}
	else
	{
		ft_putnbr(str, n / 10);
		ft_putnbr(str, n % 10);
	}
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*result;
	int				len;

	len = count_digits(n) + 1;
	result = (char *)ft_calloc(len, sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		num = -n;
		ft_putnbr(result + 1, num);
	}
	else
	{
		num = n;
		ft_putnbr(result, num);
	}
	return (result);
}
