/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:44:53 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/17 13:48:32 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	safe_print(t_table *table, int philo_id, const char *msg, const char *color)
{
	long	timestamp;

	pthread_mutex_lock(&table->table_mutex);
	if (!table->end_simulation)
	{
		timestamp = (get_time() - table->start_simulation) / 1000;
		printf("%s%ld %d %s\n"RESET, color, timestamp, philo_id, msg);
	}
	pthread_mutex_unlock(&table->table_mutex);
}

long	calculate_thinking_time(t_table *table)
{
	long	thinking_time;

	thinking_time = (table->time2die - table->time2eat - table->time2sleep);
	if (thinking_time < 0)
		thinking_time = 0;
	if (thinking_time > 600)
		thinking_time = 600;
	return (thinking_time);
}
