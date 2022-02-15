/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:16:47 by dim               #+#    #+#             */
/*   Updated: 2022/02/15 20:17:16 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (++i <= info->num_of_philo)
	{
		if (pthread_create(&(info->philosophers[i].tid),
				NULL, ft_philosopher, (void *)&info->philosophers[i]) != 0)
			return (ft_free(info, 31));
	}
	check_philos(info);
	i = 0;
	while (++i <= info->num_of_philo)
		pthread_join(info->philosophers[i].tid, NULL);
	return (1);
}
