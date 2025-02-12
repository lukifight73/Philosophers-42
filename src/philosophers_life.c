/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_life.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/12 11:35:58 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_life_philosophers_thinker(t_philo *current, t_data *data, int fork1,
		int fork2)
{
	if (ft_i_said_let_them_think(current))
		return ;
	pthread_mutex_lock(&current->mutex);
	current->state = FORK;
	pthread_mutex_unlock(&current->mutex);
	while ((!fork1 || !fork2))
	{
		is_alive(current, data);
		if (!fork1 && !is_dead(data) && !all_philo_eaten(data))
			ft_life_philosophers_get_own_fork(current, data, &fork1);
		if (!fork2 && !is_dead(data) && !all_philo_eaten(data))
			ft_life_philosophers_get_due_fork(current, data, &fork2);
		if (is_dead(data) || all_philo_eaten(data))
			return ;
	}
	pthread_mutex_lock(&current->mutex);
	current->state = EAT;
	current->last_time_start_eat = (int)get_time_in_ms() - data->time_start;
	pthread_mutex_unlock(&current->mutex);
	if (is_dead(data) || all_philo_eaten(data))
		return ;
	pthread_mutex_lock(&data->write->mutex);
	printf("%d %d is eating\n\n", current->last_time_start_eat, current->phil_);
	pthread_mutex_unlock(&data->write->mutex);
}

int	ft_life_philosophers_eating(t_philo *current, t_data *data)
{
	time_t	time;

	time = (current->last_time_start_eat + data->t_to_eat
			- ((int)get_time_in_ms() - data->time_start)) * 1000;
	if (time > 0 || is_dead(data) || all_philo_eaten(data))
		return (usleep(10), 1);
	pthread_mutex_lock(&current->mutex);
	current->fork = 1;
	current->nb_eat++;
	current->last_time_finish_eat = (int)get_time_in_ms() - data->time_start;
	pthread_mutex_unlock(&current->mutex);
	pthread_mutex_lock(&current->prev->mutex);
	current->prev->fork = 1;
	pthread_mutex_unlock(&current->prev->mutex);
	if (is_dead(data) || all_philo_eaten(data))
		return (1);
	pthread_mutex_lock(&current->mutex);
	pthread_mutex_lock(&data->write->mutex);
	printf("%d %d is sleeping\n\n", current->last_time_finish_eat,
		current->phil_);
	pthread_mutex_unlock(&data->write->mutex);
	current->state = SLEEP;
	pthread_mutex_unlock(&current->mutex);
	return (0);
}

void	ft_life_philosophers(t_philo *current, t_data *data)
{
	time_t	time;

	if (current->state == PIPE)
		ft_start_waiting(current);
	if ((current->state == THINK || current->state == FORK) && !is_dead(data)
		&& !all_philo_eaten(data))
		ft_life_philosophers_thinker(current, data, 0, 0);
	else if (current->state == EAT && !is_dead(data) && !all_philo_eaten(data))
		ft_life_philosophers_eating(current, data);
	else if (current->state == SLEEP && !is_dead(data)
		&& !all_philo_eaten(data))
	{
		time = (current->last_time_finish_eat + data->t_to_sleep
				- ((int)get_time_in_ms() - data->time_start)) * 1000;
		if (time > 0)
		{
			usleep(10);
			return ;
		}
		time = (int)get_time_in_ms() - data->time_start;
		ici(data, current, time);
	}
}

void	*thread_routine(void *data1)
{
	int		philo_nb;
	t_philo	*current;
	t_data	*data;

	data = (t_data *)data1;
	pthread_mutex_lock(&data->mutex);
	philo_nb = data->indice_philo;
	data->indice_philo++;
	pthread_mutex_unlock(&data->mutex);
	current = data->philo;
	while (current->phil_ != philo_nb)
		current = current->next;
	pthread_mutex_lock(&current->mutex);
	if (philo_nb % 2 == 0)
		current->state = FORK;
	else
		current->state = PIPE;
	pthread_mutex_unlock(&current->mutex);
	while (!is_dead(data) && !all_philo_eaten(data))
	{
		is_alive(current, data);
		ft_life_philosophers(current, data);
	}
	return (data);
}

int	let_them_think(t_data *data)
{
	int	i;

	i = 1;
	get_time_start(data);
	while (i <= data->nb_philo && data->nb_philo > 1)
	{
		pthread_create(&data->current->thread, NULL, thread_routine, data);
		data->current = data->current->next;
		i++;
	}
	data->current = data->philo;
	i = 1;
	while (i <= data->nb_philo && data->nb_philo > 1)
	{
		pthread_join(data->current->thread, NULL);
		data->current = data->current->next;
		i++;
	}
	pthread_mutex_lock(&data->mutex);
	data->start = 1;
	pthread_mutex_unlock(&data->mutex);
	if (data->nb_philo == 1)
		ft_lone_philo_life(data);
	ft_data_liberator(data);
	return (0);
}
