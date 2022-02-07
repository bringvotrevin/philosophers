/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:49:52 by dim               #+#    #+#             */
/*   Updated: 2022/02/07 16:27:37 by dim              ###   ########.fr       */
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
}

t_info	*parsing(int argc, char **argv)
{
	t_info	*info;

	if (check_error(argc))
		return (NULL);
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info);
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	if (info->num_of_philo < 0 && info->time_die < 0
		info->num_must_eat = ft_atoi(argv[5]);
			&& info->time_eat < 0 && info->time_sleep < 0)
		return (NULL);
	return (info);
}