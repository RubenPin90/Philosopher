/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:51:57 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/30 14:37:34 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

static void	free_data(t_data *data)
{
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		if (data->philo != NULL)
		{
			pthread_mutex_destroy(&data->philo[i].m_lmeal);
			pthread_mutex_destroy(&data->philo[i].m_full);
		}
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->m_done);
	pthread_mutex_destroy(&data->m_alive);
	free_data(data);
}

void	ft_puterr(char *flag)
{
	int	i;

	i = 0;
	while (flag[i])
		i++;
	write (2, flag, i);
}

int	ft_error(char *flag, t_data *data)
{
	ft_puterr(flag);
	if (data)
		ft_exit(data);
	return (FAIL);
}
