/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:38:04 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/06 17:47:13 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_all_threads(t_table *table)
{
	while (true)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->all_threads_ready)
		{
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->table_mutex);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	
	pthread_mutex_lock(&philo->table->table_mutex);
	if (! philo->table->end_simulation)
	{
		timestamp = gettime(TIME_SINCE_START);
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->table_mutex);
}

void	monitor_philos(t_table *table)
{
	int		i;
	long	time_since_meal;
	
	while (true)
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->table_mutex);
			time_since_meal = gettime(TIME_SINCE_START) - table->philos[i].last_meal_time;
			
			if (time_since_meal > table->time2die / 1000)
			{
				printf("%ld %d died\n", gettime(TIME_SINCE_START), table->philos[i].id);
				table->end_simulation = true;
				pthread_mutex_unlock(&table->table_mutex);
				return ;
			}
			
			if (table->nbr_limits_meals != -1 && 
				table->philos[i].meals_count >= table->nbr_limits_meals)
				table->philos[i].full = true;
			pthread_mutex_unlock(&table->table_mutex);
		}
		
		if (all_philos_full(table))
			break ;
		usleep(1000);
	}
}

bool	all_philos_full(t_table *table)
{
	int	i;
	bool	all_full;
	
	if (table->nbr_limits_meals == -1)
		return (false);
	
	all_full = true;
	i = -1;
	pthread_mutex_lock(&table->table_mutex);
	while (++i < table->philo_nbr)
	{
		if (!table->philos[i]. full)
		{
			all_full = false;
			break ;
		}
	}
	if (all_full)
		table->end_simulation = true;
	pthread_mutex_unlock(&table->table_mutex);
	return (all_full);
}

long	gettime(int flag)
{
	struct timeval	tv;
	static long		start_time = 0;

	gettimeofday(&tv, NULL);
	if (flag == TIME_IN_MS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (flag == TIME_IN_US)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else if (flag == TIME_SINCE_START)
	{
		if (start_time == 0)
			start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time);
	}
	return (0);
}

void	precise_usleep(long usec)
{
	long	start;

	start = gettime(TIME_IN_US);
	while ((gettime(TIME_IN_US) - start) < usec)
		usleep(500);
}
