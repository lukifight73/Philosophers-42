/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:34:08 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/12 11:36:57 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define EAT 1   //
# define SLEEP 2 //   <<
# define THINK 3
# define FORK 4
# define DIE 0
# define PIPE 5 // PIPE

# include <bsd/string.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				phil_;
	int				fork;
	int				own_fork;
	int				due_fork;
	int				state;
	int				nb_eat;
	int				last_time_finish_eat;
	int				last_time_start_eat;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

typedef struct s_write
{
	pthread_mutex_t	mutex;
}					t_write;

typedef struct s_data
{
	struct s_philo	*philo;
	struct s_philo	*current;
	struct s_write	*write;
	pthread_t		*thread;
	int				start;
	int				nb_philo;
	int				indice_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				time_start;
	pthread_mutex_t	mutex;
	int				nb_philo_eat;
	int				one_philo_died;
}					t_data;

time_t				get_time_in_ms(void);
int					ft_check_init_data(int ac, char **av, t_data *data);
int					create_philosophers(t_data *data);
int					ft_init_data_malloc(t_data *data);
int					is_dead(t_data *data);
int					is_alive(t_philo *current, t_data *data);
int					all_philo_eaten(t_data *data);
int					let_them_think(t_data *data);
int					ft_atoi(const char *nptr);
int					ft_i_said_let_them_think(t_philo *current);
int					ft_what_thinking(t_philo *current, int prev_state,
						int next_state, int next_eat);
int					think_again(t_philo *current, int prev_eat, int next_eat,
						int indice);
int					ft_life_philosophers_eating(t_philo *current, t_data *data);
void				*thread_routine(void *data1);
void				ft_life_philosophers(t_philo *current, t_data *data);
void				ft_life_philosophers_thinker(t_philo *current, t_data *data,
						int fork1, int fork2);
void				get_time_start(t_data *data);
void				init_philosophers(t_data *data, t_philo *philo);
void				malloc_fail(void);
void				ft_data_liberator(t_data *data);
void				ft_philo_liberator(t_data *data);
void				ft_mutex_destroyer(t_data *data);
void				ft_life_philosophers_get_own_fork(t_philo *current,
						t_data *data, int *fork);
void				ft_life_philosophers_get_due_fork(t_philo *current,
						t_data *data, int *fork);
void				ft_lone_philo_life(t_data *data);
void				ft_start_waiting(t_philo *current);
void				ici(t_data *data, t_philo *current, time_t time);
void				ft_get_prev(t_philo *current, int *prev_state,
						int *prev_last_eat);
#endif
