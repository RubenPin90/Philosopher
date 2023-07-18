/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:51:57 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/18 11:49:48 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	free_data(t_data *data)
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
	free(data);
	data = NULL;
}

void	ft_exit(t_data *data, bool check)
{
	int i;

	i = -1;
	if (check == true)
	{
		while (++i < data->args.num_phil)
			pthread_mutex_destroy(&data->philo[i].m_lmeal);
		i = -1;
		while (++i < data->args.num_phil)
			pthread_mutex_destroy(&data->forks[i]);
		if (data->write != NULL)
			pthread_mutex_destroy(data->write);
		if (data->m_done != NULL)
			pthread_mutex_destroy(data->m_done);
		if (data->m_alive != NULL)
			pthread_mutex_destroy(data->m_alive);
	}
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

int	ft_error(char *flag, t_data *data, bool check)
{
	ft_puterr(flag);
	if (data)
		ft_exit(data, check);
	return (FAIL);
}

void	free_null(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}	
}
