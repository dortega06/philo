/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:04:38 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/06 17:37:51 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/*
void	dinner_start(t_table *table)
{
	if (table->nbr_limits_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else
		while (++i < table->philo_nbr)
		{
			
		}
	
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);

	return (NULL);
}*/

#include "../philo.h"

static void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->first_fork->fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->second_fork->fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->second_fork->fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->first_fork->fork);
		print_status(philo, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->last_meal_time = gettime(TIME_SINCE_START);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->table->table_mutex);
	
	print_status(philo, "is eating");
	precise_usleep(philo->table->time2eat);
	
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->table->time2sleep);
}

static bool	simulation_finished(t_philo *philo)
{
	bool finished;
	
	pthread_mutex_lock(&philo->table->table_mutex);
	finished = philo->table->end_simulation;
	pthread_mutex_unlock(&philo->table->table_mutex);
	return (finished);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->last_meal_time = gettime(TIME_SINCE_START);
	pthread_mutex_unlock(&philo->table->table_mutex);
	
	if (philo->id % 2 == 0)
		usleep(1000);
	
	while (! simulation_finished(philo))
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	if (table->nbr_limits_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		printf("0 1 has taken a fork\n");
		precise_usleep(table->time2die);
		printf("%ld 1 died\n", table->time2die / 1000);
		return ;
	}
	
	pthread_mutex_init(&table->table_mutex, NULL);
	table->start_simulation = gettime(TIME_IN_MS);
	table->all_threads_ready = false;
	
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				dinner_simulation, &table->philos[i]) != 0)
			return ;
	}
	
	pthread_mutex_lock(&table->table_mutex);
	table->all_threads_ready = true;
	pthread_mutex_unlock(&table->table_mutex);
	
	monitor_philos(table);
	
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
}
