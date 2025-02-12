/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:32:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/10 11:11:31 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data) * 1);
	if (!data)
		return (malloc_fail(), 1);
	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments\n");
		return (free(data), 1);
	}
	if (ft_check_init_data(ac, av, data))
		return (free(data), 1);
	if (ft_init_data_malloc(data))
		return (free(data), malloc_fail(), 1);
	let_them_think(data);
	return (0);
}
