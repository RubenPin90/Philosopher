/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:51:57 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/20 14:26:36 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	free_data(t_data *data)
{
	if (data->m_forks)
		free_null((void *)data->m_forks);
	if (data->philo)
		free_null((void *)data->philo);
	free_null((void *)data);
}

void	ft_exit(t_data *data, bool check)
{
	int	i;

	i = -1;
	if (check == true)
	{
		while (++i < data->args.num_phil)
			pthread_mutex_destroy(&data->philo[i].m_lmeal);
		i = -1;
		while (++i < data->args.num_phil)
			pthread_mutex_destroy(&data->m_forks[i]);
		if (data->m_print != NULL)
			cleanup_mutex(data->m_print);
		if (data->m_done != NULL)
			cleanup_mutex(data->m_done);
		if (data->m_alive != NULL)
			cleanup_mutex(data->m_alive);
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
