/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:  2025/12/29 19:19:19 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/17 15:35:04 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	clean_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->forks[i].fork);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->philos);
	free(table->forks);
}

void	error_exit(const char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean_table(&table);
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}
