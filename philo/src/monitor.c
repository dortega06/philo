/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:  2026/01/06 17:04:38 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/17 15:37:39 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	check_death(t_table *table)
{
	int		i;
	long	time_since_meal;
	long	current_time;
	long	timestamp;
	
	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->table_mutex);
		current_time = get_time();
		time_since_meal = current_time - table->philos[i].last_meal_time;
/*		if (time_since_meal > (table->time2die * 0.8))  // Si más de 300ms
		     printf("DEBUG: Philo %d - time_since_meal=%ld, limit=%ld\n",
		            table->philos[i].id, time_since_meal/1000, table->time2die/1000);*/
		if (time_since_meal >= table->time2die)
		{
			timestamp = (current_time - table->start_simulation) / 1000;
			printf(RED"%ld %d died\n"RESET, timestamp, table->philos[i].id);
			table->end_simulation = true;
			pthread_mutex_unlock(&table->table_mutex);
			return (true);
		}
		pthread_mutex_unlock(&table->table_mutex);
	}
	return (false);
}

static bool	check_all_full(t_table *table)
{
	int	i;
	int	full_count;

	if (table->nbr_limits_meals == -1)
		return (false);
	i = -1;
	full_count = 0;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->philos[i]. full)
			full_count++;
		pthread_mutex_unlock(&table->table_mutex);
	}
	if (full_count == table->philo_nbr)
	{
		set_bool(&table->table_mutex, &table->end_simulation, true);
		return (true);
	}
	return (false);
}

void	monitor(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->end_simulation))
	{
		if (check_death(table) || check_all_full(table))
			break;
		usleep(100);
	}
}
