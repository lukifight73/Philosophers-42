/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/10 11:01:12 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	if (data->one_philo_died)
	{
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex);
	return (0);
}

int	all_philo_eaten(t_data *data)
{
	t_philo	*current;
	int		i;
	int		count;

	if (data->nb_philo_eat == -56789)
		return (0);
	current = data->philo;
	i = 1;
	count = 0;
	while (i <= data->nb_philo)
	{
		pthread_mutex_lock(&current->mutex);
		if (current->nb_eat >= data->nb_philo_eat)
			count++;
		pthread_mutex_unlock(&current->mutex);
		current = current->next;
		i++;
	}
	if (count == data->nb_philo)
		return (1);
	return (0);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	get_time_start(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->time_start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	is_alive(t_philo *current, t_data *data)
{
	int	time;

	time = -(current->last_time_start_eat - ((int)get_time_in_ms()
				- data->time_start));
	if (time >= data->t_to_die)
	{
		time = ((int)get_time_in_ms() - data->time_start);
		pthread_mutex_lock(&data->mutex);
		if (data->one_philo_died == 1)
		{
			pthread_mutex_unlock(&data->mutex);
			return (1);
		}
		data->one_philo_died = 1;
		pthread_mutex_unlock(&data->mutex);
		pthread_mutex_lock(&data->write->mutex);
		printf("%d %d died\n\n", time, current->phil_);
		pthread_mutex_unlock(&data->write->mutex);
		return (1);
	}
	return (0);
}
