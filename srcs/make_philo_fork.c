/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:10:13 by dim               #+#    #+#             */
/*   Updated: 2022/02/17 17:20:12 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	malloc_ptr(t_info *info)
{
	info->philosophers = (t_personal *)malloc(sizeof
			(t_personal) * (info->num_of_philo + 1));
	if (info->philosophers == NULL)
		return (ft_free(info, 1));
	info->forks = (pthread_mutex_t *)malloc(sizeof
			(pthread_mutex_t) * (info->num_of_philo + 1));
	if (info->forks == NULL)
		return (ft_free(info, 3));
	return (1);
}

void	init_mutex(t_info *info)
{
	pthread_mutex_init(&info->mutex_for_print, NULL);
	pthread_mutex_init(&info->mutex_for_check, NULL);
}

int	make_philo_fork(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	status = malloc_ptr(info);
	if (!status)
		return (status);
	init_mutex(info);
	while (i++ < info->num_of_philo)
	{
		pthread_mutex_init(&(info->forks[i]), NULL);
		info->philosophers[i].name = i;
		info->philosophers[i].cnt_eaten = 0;
		info->philosophers[i].time_last_eat = info->start_time;
		info->philosophers[i].info = info;
		info->philosophers[i].left_fork = &info->forks[i];
		if (info->num_of_philo == 1)
			info->philosophers[i].right_fork = &info->forks[i];
		else if (i + 1 == info->num_of_philo)
			info->philosophers[i].right_fork = &info->forks[info->num_of_philo];
		else
			info->philosophers[i].right_fork
				= &info->forks[(i + 1) % info->num_of_philo];
	}
	return (1);
}
