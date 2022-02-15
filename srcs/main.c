/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:39:19 by dim               #+#    #+#             */
/*   Updated: 2022/02/15 19:55:57 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_personal *philo)
{
	// pthread_mutex_lock(philo->info->mutex_for_check);
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
		// printf("------%d philo has eaten %d times------\n", philo->name, philo->cnt_eaten);
	}
	// pthread_mutex_unlock(philo->info->mutex_for_check);
}

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
		// if (philo->info->num_must_eat == philo->cnt_eaten)
		// 	break;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	check_philos(t_info *info)
{
	int i;

	i = 0;
	while (info->alive)
	{
		i = 0;
		while (++i <= info->num_of_philo && info->alive)
		{
			pthread_mutex_lock(info->mutex_for_check);
			if (info->done_philo == info->num_of_philo)
			{
				// pthread_mutex_lock(info->mutex_for_check);
				info->alive = false;
				// pthread_mutex_unlock(info->mutex_for_check);
			}
			else if (get_mstime() - info->philosophers[i].time_last_eat
				> info->time_die)
			{
				// pthread_mutex_lock(info->mutex_for_check);
				print_state(&info->philosophers[i], "died");
				info->alive = false;
				// pthread_mutex_unlock(info->mutex_for_check);
			}
			pthread_mutex_unlock(info->mutex_for_check);
		}
	}
}

int		create_thread(t_info *info)
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

int		malloc_ptr(t_info *info)
{
	info->philosophers = (t_personal *)malloc(sizeof
							(t_personal) * (info->num_of_philo + 1));
	if (info->philosophers == NULL)
		return (ft_free(info, 1));
	info->forks = (pthread_mutex_t *)malloc(sizeof(
						pthread_mutex_t) * (info->num_of_philo + 1));
	if (info->forks == NULL)
		return (ft_free(info, 3));
	info->mutex_for_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (info->mutex_for_print == NULL)
		return (ft_free(info, 7));
	info->mutex_for_check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (info->mutex_for_check == NULL)
		return (ft_free(info, 15));
	return (1);
}

int		make_philo_fork(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	status = malloc_ptr(info);
	if (!status)
		return (status);
	pthread_mutex_init(info->mutex_for_print, NULL);
	pthread_mutex_init(info->mutex_for_check, NULL);
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
			info->philosophers[i].right_fork =
				&info->forks[(i + 1) % info->num_of_philo];
	}
	return (1);
}

int		main(int argc, char *argv[])
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
