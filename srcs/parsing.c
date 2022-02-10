/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:49:52 by dim               #+#    #+#             */
/*   Updated: 2022/02/11 01:16:52 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex_destroy(t_info *info)
{
	int i;

	i = 0;
	while(++i < info->num_of_philo)
		pthread_mutex_destroy(&info->forks[i]);
}

int	ft_free(t_info *info, char flag)
{
	char	bit;

	bit = 0b00000001;
	if (flag & bit)
		free(info);
	if (flag & bit<<1)
		free(info->philosophers);
	if (flag & bit<<2)
		free(info->forks);
	if (flag & bit<<3)
	{
		free(info->mutex_for_print);
		ft_mutex_destroy(info);
		pthread_mutex_destroy(info->mutex_for_print);
	}
	return (0);
}

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

	if (check_error(argc))
		return (NULL);
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	init_info(info);
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->start_time = get_mstime();
	printf("time : %ld\n", info->start_time);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	if (info->num_of_philo < 0 || info->time_die < 0
		|| info->time_eat < 0 || info->time_sleep < 0)
		return (NULL);
	return (info);
}