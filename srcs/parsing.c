/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:49:52 by dim               #+#    #+#             */
/*   Updated: 2022/02/10 01:37:39 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int		check_error(int argc)
{
	if (argc == 5 || argc == 6)
		return (0);
	return (-1);
}

void	init_info(t_info *info)
{
	info->num_of_philo = 0;
	info->time_die = 0;
	info->time_eat = 0;
	info->time_sleep = 0;
	info->num_must_eat = -1;
	info->start_time = 0;
}

t_info	*parsing(int argc, char **argv)
{
	t_info	*info;
	struct timeval	time;

	if (check_error(argc))
		return (NULL);
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info);
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	gettimeofday(&time, NULL);
	info->start_time = (time.tv_usec);
	printf("time : %ld\n", info->start_time);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	if (info->num_of_philo < 0 || info->time_die < 0
		|| info->time_eat < 0 || info->time_sleep < 0)
		return (NULL);
	return (info);
}