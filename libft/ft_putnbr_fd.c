/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:30:08 by emichels          #+#    #+#             */
/*   Updated: 2023/11/14 15:13:48 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	c;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num < 10)
	{
		c = num + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(num / 10, fd);
		c = num % 10 + '0';
		write(fd, &c, 1);
	}
}
