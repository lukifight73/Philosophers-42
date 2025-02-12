/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/12 11:19:31 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_data *data, t_philo *philo)
{
	int		i;
	t_philo	*current;

	current = philo;
	i = 1;
	while (i <= data->nb_philo)
	{
		current->phil_ = i;
		current->fork = 1;
		current->state = THINK;
		current->nb_eat = 0;
		current->last_time_start_eat = 0;
		current->last_time_finish_eat = 0;
		current->data = data;
		pthread_mutex_init(&current->mutex, NULL);
		current = current->next;
		i++;
	}
}

void	malloc_fail(void)
{
	write(2, "Malloc error\n", 13);
	return ;
}

int	create_philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_philo	*current;

	philo = (t_philo *)malloc(1 * sizeof(t_philo));
	if (!philo)
		return (1);
	data->philo = philo;
	current = philo;
	i = 1;
	while (i < data->nb_philo)
	{
		current->next = (t_philo *)malloc(1 * sizeof(t_philo));
		if (!current->next)
			return (ft_philo_liberator(data), 1);
		current->next->prev = current;
		current = current->next;
		i++;
	}
	current->next = philo;
	philo->prev = current;
	init_philosophers(data, philo);
	data->current = philo;
	return (0);
}

int	ft_init_data_malloc(t_data *data)
{
	data->thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->thread)
		return (1);
	if (create_philosophers(data))
		return (free(data->thread), 1);
	data->write = (t_write *)malloc(sizeof(t_write) * 1);
	if (!data->write)
		return (free(data->thread), 1);
	pthread_mutex_init(&data->write->mutex, NULL);
	data->indice_philo = 1;
	data->start = 0;
	return (0);
}

int	ft_check_init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = -1;
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo < 1)
		i = printf("Invalid number : too few philosophers\n");
	data->t_to_die = ft_atoi(av[2]);
	if (data->t_to_die < 1)
		i = printf("Invalid timespan : insuficient time to die\n");
	data->t_to_eat = ft_atoi(av[3]);
	if (data->t_to_eat < 1)
		i = printf("Invalid timespan : insuficient time to eat\n");
	data->t_to_sleep = ft_atoi(av[4]);
	if (data->t_to_sleep < 1)
		i = printf("Invalid timespan : insuficient time to sleep\n");
	data->nb_philo_eat = -56789;
	if (ac == 6)
		data->nb_philo_eat = ft_atoi(av[5]);
	if (data->nb_philo_eat != -56789 && data->nb_philo_eat < 0)
		i = printf("Invalid number : insuficient number of meals\n");
	if (i != -1)
		return (1);
	data->one_philo_died = 0;
	pthread_mutex_init(&data->mutex, NULL);
	return (0);
}
