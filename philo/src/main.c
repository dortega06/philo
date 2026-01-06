/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:19:19 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/06 16:58:39 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);//error check, filling table table
		data_init(&table);// creando 
		dinner_start(&table);
		//leaks
	}
	else
		printf("error");
}
