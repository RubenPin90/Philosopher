/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:46:28 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/22 16:51:10 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	result;

	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

int	check_args(int count, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (av[i][j])
		{
			if (j < 48 && j > 57)
				return (FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

void	print_data(t_input args)
{
	printf("number_of_philosophers: %d\n", args.num_phil);
	printf("time_to_die: %lld\n", args.time_to_die);
	printf("time_to_eat: %lld\n", args.time_to_eat);
	printf("time_to_sleep: %lld\n", args.time_to_sleep);
	printf("number_of_times_phil_must_eat: %d\n", args.phil_hunger);
}

long long	get_time(void)
{
	struct timeval	start;
	long long		tmp;

	if (gettimeofday(&start, NULL) == -1)
		return (-1);
	tmp = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (tmp);
}

