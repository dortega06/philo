/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:19:19 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/03 19:03:13 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	if (ac == 5 | ac == 6)
	{
		parse_input(&table, av);//error check, filling table table
	//	data_init();// creando 
	//	dinner_start();
		//leaks
	}
	else
		printf("error");
}
