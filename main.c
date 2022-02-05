/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:39:19 by dim               #+#    #+#             */
/*   Updated: 2022/02/05 20:06:34 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	philosopher()
// {
// 	int i;

// 	i = 0;
// 	while ()
// 	{
// 		i = 1;
// 	}
// }

int		create_thread(t_info *info)
{
	(void)info;
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
		info->philosophers[i].info = info;
		info->philosophers[i].left_fork = &info->forks[i];
		info->philosophers[i].right_fork =
			&info->forks[i + 1 / info->num_of_philo];
		info->philosophers[i].mutex_print = &(info->mutex_for_print);
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

