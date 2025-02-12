/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone_philo_sad_life.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/07 17:00:33 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lone_philo_life(t_data *data)
{
	time_t	time;

	time = (int)get_time_in_ms() - data->time_start;
	printf("%ld %d has taken a fork\n\n", time, data->current->phil_);
	while (time < data->t_to_die)
	{
		usleep(100);
		time = (int)get_time_in_ms() - data->time_start;
	}
	printf("%ld %d died\n\n", time, data->current->phil_);
	data->one_philo_died = 1;
}
