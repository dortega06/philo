/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:59:53 by dortega-          #+#    #+#             */
/*   Updated: 2026/01/17 12:53:19 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

const char *valid_input(const char *str)
{
	int	len;
	const char *nbr;

	len = 0;
	while (ft_isspace((int)*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("negative numbers not allowed");
	if (!ft_isdigit((int)*str))
		error_exit("not a valid number");
	nbr = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		error_exit("value too large");
	return (nbr);
}

long int	ft_atol(const char *str)
{
	long int	nbr;

	nbr = 0;
	str = valid_input(str);
	while (ft_isdigit((int)*str))
		nbr = (nbr * 10) + (*str++ - 48);
	if (nbr > INT_MAX)
		error_exit("number exceeds INT_MAX");
	return (nbr);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time2die = ft_atol(av[2]) * 1000;
	table->time2eat = ft_atol(av[3]) * 1000;
	table->time2sleep = ft_atol(av[4]) * 1000;
/*	if (table->time2die < 6e4 || table->time2eat < 6e4
		|| table->time2sleep < 6e4)
		error_exit("use timestamps greater than 60ms");*/
	if (av[5])
		table->nbr_limits_meals = ft_atol(av[5]);
	else
		table->nbr_limits_meals = -1;
}
