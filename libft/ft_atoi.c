/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:40:56 by emichels          #+#    #+#             */
/*   Updated: 2023/11/16 09:31:28 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	counter;
	int	result;
	int	negative;
	int	sign;

	counter = 0;
	result = 0;
	negative = 0;
	sign = 0;
	while ((str[counter] >= 9 && str[counter] <= 13) || str[counter] == ' ')
		counter++;
	while (str[counter] == '-' || str[counter] == '+')
	{
		if (str[counter++] == '-')
			negative++;
		sign++;
	}
	if (sign > 1)
		return (0);
	while (str[counter] >= '0' && str[counter] <= '9')
		result = result * 10 + (str[counter++] - '0');
	if (negative == 1)
		return (result * -1);
	return (result);
}
