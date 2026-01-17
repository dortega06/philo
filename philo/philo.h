/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:05:27 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/06 17:48:43 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# define TIME_IN_MS 0
# define TIME_IN_US 1
# define TIME_SINCE_START 2

typedef pthread_mutex_t t_mtx;
typedef struct s_philo t_philo;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_table
{
	long	philo_nbr;
	long	time2die;
	long	time2eat;
	long	time2sleep;
	long	nbr_limits_meals;
	long	start_simulation;
	bool	end_simulation;
	bool	all_threads_ready;
	t_mtx	table_mutex;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;


void	parse_input(t_table *table, char **av);

// Init
void	data_init(t_table *table);

// Dinner
void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);

// Utils
long	gettime(int flag);
void	precise_usleep(long usec);
void	wait_all_threads(t_table *table);
void	print_status(t_philo *philo, char *status);
void	monitor_philos(t_table *table);
bool	all_philos_full(t_table *table);
/******************************************************************************/
/*                                 Parser                                     */
/******************************************************************************/

/******************************************************************************/
/*                              Time Functions                                */
/******************************************************************************/

/******************************************************************************/
/*                                  Utils                                     */
/******************************************************************************/

/******************************************************************************/
/*                                  Error                                     */
/******************************************************************************/

#endif
