/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:52:38 by dim               #+#    #+#             */
/*   Updated: 2022/02/11 21:24:25 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_mstime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long	usleep_time)
{
	long	timer;

	timer = usleep_time + get_mstime();
	while (timer > get_mstime())
		usleep(100);
}

int		error_p(char *msg)
{
	printf("%s\n", msg);
	return (0);
}

int		ft_atoi(char *str)
{
	int	num;

	num = 0;
	while((*str >= '0' && *str <= '9'))
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return (num);
}
