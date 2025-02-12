/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/10 11:07:06 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex_destroyer(t_data *data)
{
	t_philo	*current;
	int		i;

	current = data->philo;
	i = 1;
	while (i <= data->nb_philo)
	{
		pthread_mutex_destroy(&current->mutex);
		current = current->next;
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}

void	ft_philo_liberator(t_data *data)
{
	t_philo	*current;
	t_philo	*temp;
	int		i;

	current = data->philo;
	i = 1;
	while (i <= data->nb_philo)
	{
		if (i < data->nb_philo)
			temp = current->next;
		free(current);
		if (i < data->nb_philo)
			current = temp;
		i++;
	}
}

void	ft_data_liberator(t_data *data)
{
	ft_mutex_destroyer(data);
	ft_philo_liberator(data);
	free(data->thread);
	free(data->write);
	free(data);
}
