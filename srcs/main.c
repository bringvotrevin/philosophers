/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:39:19 by dim               #+#    #+#             */
/*   Updated: 2022/02/10 20:44:54 by dim              ###   ########.fr       */
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

void	print_state(t_personal *philo, char *msg, int eat_flag)
{
	long	time;

	pthread_mutex_lock(philo->info->mutex_for_print);
	time = get_mstime() - philo->info->start_time;
	printf("%ldms", time);
	printf(" %d %s\n", philo->name, msg);
	if (eat_flag)
	{
		philo->time_last_eat = time;
		philo->cnt_eaten++;
	}
	pthread_mutex_unlock(philo->info->mutex_for_print);
}

void	eating(t_personal *philo)
{
	print_state(philo, "is eating", 1);
	ft_usleep(philo->info->time_eat);
}

void	sleeping(t_personal *philo)
{
	print_state(philo, "is sleeping", 0);
	ft_usleep(philo->info->time_sleep);
}

void	thinking(t_personal *philo)
{
	print_state(philo, "is thinking", 0);
}

void	philo_odd(t_personal *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork", 0);
	eating(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	sleeping(philo);
	thinking(philo);
}

void	philo_even(t_personal *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork", 0);
	eating(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	sleeping(philo);
	thinking(philo);
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
		if (philo->info->num_must_eat == philo->cnt_eaten)
			break;
		// sleeping(philo);
		// thinking(philo);
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
	info->philosophers = NULL;
	if (info->philosophers == NULL)
	{
		ft_free(info, 8);
		return (-1);
	}
	info->forks = (pthread_mutex_t *)malloc(sizeof(
						pthread_mutex_t) * (info->num_of_philo + 1));
	if (info->forks == NULL)
	{
		ft_free(info, 1);
		return (-1);
	}
	info->mutex_for_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (info->mutex_for_print == NULL)
	{
		ft_free(info, 3);
		return (-1);
	}
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
	pthread_mutex_init(&(info->mutex_for_print), NULL);
	while (i++ < info->num_of_philo)
	{
		pthread_mutex_init(&(info->forks[i]), NULL);
		info->philosophers[i].name = i;
		info->philosophers[i].cnt_eaten = 0;
		// info->philosophers[i].num_must_eat = info->num_must_eat;
		info->philosophers[i].info = info;
		info->philosophers[i].left_fork = &info->forks[i];
		info->philosophers[i].right_fork =
			&info->forks[(i + 1) % info->num_of_philo];
		// info->philosophers[i].m_print = &(info->mutex_for_print);
	}
	return (1);
}
void	ft_mutex_destroy(t_info *info)
{
	int i;

	i = 0;
	while(++i < info->num_of_philo)
		pthread_mutex_destroy(info->fork[i], NULL);
}

void	ft_free(t_info *info, char flag)
{
	char	bit;

	bit = 0b00000001;
	if (flag & bit)
	{
		printf("bit : 00000001\n");
		free(info);
	}
	if (flag & bit<<1)
	{
		printf("bit : 00000010\n");
		free(info->philosophers);
	}
	if (flag & bit<<2)
	{	
		printf("bit : 00000100\n");
		free(info->forks);
	}
	if (flag & bit<<3)
	{
		printf("bit : 00001000\n");
		free(info->mutex_for_print);
	}
	if (flag & bit<<4)
	{
		printf("bit : 00010000\n");
		ft_mutex_destroy(info);
		pthread_mutex_destroy()
	}
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
	ft_free(info, 15);
	return (0);
}

