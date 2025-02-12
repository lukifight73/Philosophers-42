/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/12 11:34:42 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_what_thinking(t_philo *current, int prev_state, int next_state,
		int next_eat)
{
	if (prev_state == FORK || next_state == FORK)
		return (usleep(10), 1);
	else if (prev_state == EAT && next_state == EAT)
		return (usleep(10), 0);
	else if (prev_state == SLEEP && next_state == EAT)
		return (0);
	else if (prev_state == EAT && next_state == SLEEP)
		return (0);
	else if (prev_state == SLEEP && next_state == SLEEP)
		return (0);
	else if ((prev_state == SLEEP || prev_state == EAT) && next_state == THINK)
	{
		if (current->last_time_start_eat < next_eat)
			return (0);
		else
			return (usleep(10), 0);
	}
	return (-1);
}

int	think_again(t_philo *current, int prev_eat, int next_eat, int indice)
{
	if (indice == 1)
	{
		if (current->last_time_start_eat < prev_eat)
			return (0);
		else
			usleep(10);
		return (0);
	}
	if (indice == 2)
	{
		if (current->last_time_start_eat <= prev_eat
			&& current->last_time_start_eat <= next_eat)
			return (0);
		else
			usleep(10);
		return (0);
	}
	return (0);
}

int	ft_i_said_let_them_think(t_philo *current)
{
	int	prev_state;
	int	next_state;
	int	prev_last_eat;
	int	next_last_eat;
	int	r;

	if (current->state == FORK)
		return (0);
	ft_get_prev(current, &prev_state, &prev_last_eat);
	pthread_mutex_lock(&current->next->mutex);
	next_state = current->next->state;
	next_last_eat = current->next->last_time_start_eat;
	pthread_mutex_unlock(&current->next->mutex);
	r = ft_what_thinking(current, prev_state, next_state, next_last_eat);
	if (r > 0)
		return (1);
	else if (r == 0)
		return (0);
	else if (prev_state == THINK && (next_state == EAT || next_state == SLEEP))
		return (think_again(current, prev_last_eat, next_last_eat, 1));
	else if (prev_state == THINK && next_state == THINK)
		return (think_again(current, prev_last_eat, next_last_eat, 2));
	return (0);
}

void	ft_life_philosophers_get_own_fork(t_philo *current, t_data *data,
		int *fork)
{
	time_t	time;

	pthread_mutex_lock(&current->mutex);
	if (current->fork)
	{
		pthread_mutex_lock(&data->write->mutex);
		time = (int)get_time_in_ms() - data->time_start;
		printf("%ld %d has taken a fork\n\n", time, current->phil_);
		pthread_mutex_unlock(&data->write->mutex);
		current->fork = 0;
		*fork = 1;
	}
	pthread_mutex_unlock(&current->mutex);
}

void	ft_life_philosophers_get_due_fork(t_philo *current, t_data *data,
		int *fork)
{
	time_t	time;

	pthread_mutex_lock(&current->prev->mutex);
	if (current->prev->fork)
	{
		pthread_mutex_lock(&data->write->mutex);
		time = (int)get_time_in_ms() - data->time_start;
		printf("%ld %d has taken a fork\n\n", time, current->phil_);
		pthread_mutex_unlock(&data->write->mutex);
		current->prev->fork = 0;
		*fork = 1;
	}
	pthread_mutex_unlock(&current->prev->mutex);
}
