/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:  2026/01/06 17:04:38 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/17 15:57:38 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	safe_print(philo->table, philo->id, "has taken a fork", BBLUE);
	pthread_mutex_lock(&philo->second_fork->fork);
	safe_print(philo->table, philo->id, "has taken a fork", BBLUE);
}

static void	philo_eat(t_philo *philo)
{
	take_forks(philo);	
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->last_meal_time = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->table->table_mutex);
	safe_print(philo->table, philo->id, "is eating", BMAGENTA);
	ft_usleep(philo->table->time2eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

static void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	pthread_mutex_lock(&philo->first_fork->fork);
	safe_print(philo->table, philo->id, "has taken a fork", BBLUE);
	ft_usleep(philo->table->time2die);
	pthread_mutex_unlock(&philo->first_fork->fork);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->last_meal_time = philo->table->start_simulation;
	pthread_mutex_unlock(&philo->table->table_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time2eat);
	while (!get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
	{
		philo_eat(philo);
		if (philo->meals_count == philo->table->nbr_limits_meals)
		{
			set_bool(&philo->table->table_mutex, &philo->full, true);
			break;
		}
		safe_print(philo->table, philo->id, "is sleeping", YELLOW);
		ft_usleep(philo->table->time2sleep);
		safe_print(philo->table, philo->id, "is thinking", CYAN);
		if (philo->table->philo_nbr % 2 == 1)
			ft_usleep(calculate_thinking_time(philo->table));
	}
	return (NULL);
}
/*
void	dinner_start(t_table *table)
{
	int	i;

	if (table->nbr_limits_meals == 0)
		return ;
	table->start_simulation = get_time();
	i = -1;
	while (++i < table->philo_nbr)
		table->philos[i].last_meal_time = table->start_simulation;
	if (table->philo_nbr == 1)
		pthread_create(&table->philos[0].thread_id, NULL, 
			lone_philo, &table->philos[0]);
	else
	{
		i = -1;
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, 
				dinner_simulation, &table->philos[i]);
	}
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i]. thread_id, NULL);
}*/
void dinner_start(t_table *table)
{
    int i;

    if (table->nbr_limits_meals == 0)
        return ;
    table->start_simulation = get_time();
    i = -1;
    while (++i < table->philo_nbr)
        table->philos[i].last_meal_time = table->start_simulation;
    if (table->philo_nbr == 1)
        pthread_create(&table->philos[0]. thread_id, NULL, 
            lone_philo, &table->philos[0]);
    else
    {
        i = -1;
        while (++i < table->philo_nbr)
            pthread_create(&table->philos[i]. thread_id, NULL, 
                dinner_simulation, &table->philos[i]);
    }
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    
    // Monitor BEFORE joining threads
    monitor(table);  // ← Add this line here
    
    i = -1;
    while (++i < table->philo_nbr)
        pthread_join(table->philos[i]. thread_id, NULL);
}
