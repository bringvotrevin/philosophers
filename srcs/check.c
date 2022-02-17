/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:20:31 by dim               #+#    #+#             */
/*   Updated: 2022/02/17 15:45:24 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_philos(t_info *info)
{
	int	i;

	i = 0;
	while (info->alive)
	{
		i = 0;
		while (++i <= info->num_of_philo && info->alive)
		{
			pthread_mutex_lock(&(info->mutex_for_check));
			if (info->done_philo == info->num_of_philo)
				info->alive = false;
			else if (get_mstime() - info->philosophers[i].time_last_eat
				> info->time_die)
			{
				print_state(&info->philosophers[i], "died");
				info->alive = false;
			}
			pthread_mutex_unlock(&(info->mutex_for_check));
		}
	}
}
