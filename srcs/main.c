/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:39:19 by dim               #+#    #+#             */
/*   Updated: 2022/02/15 20:21:06 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_personal *philo)
{
	print_state(philo, "is eating");
	if (philo->info->alive)
	{
		philo->time_last_eat = get_mstime();
		philo->cnt_eaten++;
		ft_mssleep(philo->info->time_eat);
		if (philo->info->num_must_eat == philo->cnt_eaten)
		{
			pthread_mutex_lock(philo->info->mutex_for_check);
			philo->info->done_philo++;
			pthread_mutex_unlock(philo->info->mutex_for_check);
		}
	}
}

void	philo_odd(t_personal *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	eating(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_even(t_personal *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	eating(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_philosopher(void *data)
{
	t_personal	*philo;

	philo = (t_personal *)data;
	if (philo->info->num_of_philo == 1)
	{
		print_state(philo, "has taken a fork");
		return (NULL);
	}
	while (philo->info->alive)
	{
		if (philo->name % 2 == 1)
			philo_odd(philo);
		else
			philo_even(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	info = parsing(argc, argv);
	if (info == NULL)
		return (error_p("argument error"));
	if (!make_philo_fork(info))
		return (error_p("creating error"));
	if (!create_thread(info))
		return (0);
	ft_free(info, 31);
	return (0);
}
