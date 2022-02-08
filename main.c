/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:39:19 by dim               #+#    #+#             */
/*   Updated: 2022/02/08 17:37:50 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(t_personal *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 - philo->info->start_time);
}

void	print_state(t_personal *philo, char *msg)
{
	long	mstime;

	pthread_mutex_lock(philo->m_print);
	printf("%ldms", get_time(philo));
	printf(" %d %s\n", philo->name, msg);
	pthread_mutex_unlock(philo->m_print);
}

void	eating(t_personal *philo)
{
	usleep(philo->info->time_eat);
	print_state(philo, "is eating");
	philo->num_eaten++;
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
	t_personal *philo;
	philo = (t_personal *)data;
	while(1)
	{
		if (philo->name % 2 == 1)
			philo_odd(philo);
		else
			philo_even(philo);
		if (philo->num_must_eat == philo->num_eaten)
			break;
		// sleeping(philo);
		// thinking(philo);
		printf("!!\n");
	}
	return (NULL);
}

int		create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (++i <= info->num_of_philo)
	{
		if (pthread_create(&(info->philosophers[i].tid),
			NULL, ft_philosopher, (void *)&info->philosophers[i]) != 0)
			return (0);
	}
	i = 0;
	while (++i <= info->num_of_philo)
		pthread_join(info->philosophers[i].tid, NULL);
	return (0);
}

int		malloc_ptr(t_info *info)
{
	info->philosophers = (t_personal *)malloc(sizeof
							(t_personal) * (info->num_of_philo + 1));
	if (info->philosophers == NULL)
		return (-1);
	info->forks = (pthread_mutex_t *)malloc(sizeof(
						pthread_mutex_t) * (info->num_of_philo + 1));
	if (info->forks == NULL)
		return (-1);
	return (1);
}

int		make_philo_fork(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	status = malloc_ptr(info);
	if (status == -1)
		return (status);
	while (i++ < info->num_of_philo)
	{
		pthread_mutex_init(&(info->forks[i]), NULL);
		info->philosophers[i].name = i;
		info->philosophers[i].num_eaten = 0;
		info->philosophers[i].num_must_eat = info->num_must_eat;
		info->philosophers[i].info = info;
		info->philosophers[i].left_fork = &info->forks[i];
		info->philosophers[i].right_fork =
			&info->forks[(i + 1) % info->num_of_philo];
		info->philosophers[i].m_print = &(info->mutex_for_print);
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
	return (0);
}

