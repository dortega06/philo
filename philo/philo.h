/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:05:27 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/03 17:49:21 by dortega-         ###   ########.fr       */
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
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

/******************************************************************************/
/*                                 Parser                                     */
/******************************************************************************/
void	parse_input(t_table *table, char **av);
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
