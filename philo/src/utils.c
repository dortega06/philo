/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:  2026/01/06 17:04:38 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/06 17:16:01 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void	ft_usleep(long usec)
{
	long	start;

	start = get_time();
	while (get_time() - start < usec)
		usleep(100);
}

void	wait_all_threads(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->all_threads_ready)
		{
			pthread_mutex_unlock(&table->table_mutex);
			break;
		}
		pthread_mutex_unlock(&table->table_mutex);
		usleep(100);
	}
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
