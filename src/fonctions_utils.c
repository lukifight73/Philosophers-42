/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/12 11:36:10 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start_waiting(t_philo *current)
{
	usleep(3000);
	pthread_mutex_lock(&current->mutex);
	current->state = THINK;
	pthread_mutex_unlock(&current->mutex);
}

void	ici(t_data *data, t_philo *current, time_t time)
{
	pthread_mutex_lock(&data->write->mutex);
	printf("%ld %d is thinking\n\n", time, current->phil_);
	pthread_mutex_unlock(&data->write->mutex);
	pthread_mutex_lock(&current->mutex);
	current->state = THINK;
	pthread_mutex_unlock(&current->mutex);
}

void	ft_get_prev(t_philo *current, int *prev_state, int *prev_last_eat)
{
	pthread_mutex_lock(&current->prev->mutex);
	*prev_state = current->prev->state;
	*prev_last_eat = current->prev->last_time_start_eat;
	pthread_mutex_unlock(&current->prev->mutex);
}
