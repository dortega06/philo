/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:18:13 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/06 17:01:26 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;
	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->last_meal_time = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

static void forks_init(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbr)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
    }
}

void    data_init(t_table *table)
{
    table->end_simulation = false;
    table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
    if (!table->philos)
        return ; // Manejar error
    table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
    if (!table->forks)
    {
        free(table->philos);
        return ; // Manejar error
    }
    
    forks_init(table);
    philo_init(table);
}
