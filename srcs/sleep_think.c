/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:13:29 by dim               #+#    #+#             */
/*   Updated: 2022/02/15 20:14:57 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_personal *philo)
{
	print_state(philo, "is sleeping");
	if (philo->info->alive)
		ft_mssleep(philo->info->time_sleep);
}

void	thinking(t_personal *philo)
{
	print_state(philo, "is thinking");
	usleep(200);
}
