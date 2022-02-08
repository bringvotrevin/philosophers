/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:39:23 by dim               #+#    #+#             */
/*   Updated: 2022/02/08 17:35:34 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_info
{
	int					num_of_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
	struct s_personal	*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_for_print;
	long				start_time;
}	t_info;

typedef struct s_personal
{
	int				name;
	int				num_eaten;
	int				num_must_eat;
	t_info			*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*m_print;
	pthread_t		tid;
}	t_personal;

t_info		*parsing(int argc, char **argv);
int			error_p(char *msg);

#endif