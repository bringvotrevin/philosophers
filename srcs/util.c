/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:52:38 by dim               #+#    #+#             */
/*   Updated: 2022/02/15 19:53:01 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_personal *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(philo->info->mutex_for_print);
	if (philo->info->alive)
	{
		time = get_mstime() - philo->info->start_time;
		printf("%ld", time);
		printf(" %d %s\n", philo->name, msg);
	}
	pthread_mutex_unlock(philo->info->mutex_for_print);
}

long	get_mstime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_mssleep(long	sleep_time)
{
	long	timer;

	timer = sleep_time + get_mstime();
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
