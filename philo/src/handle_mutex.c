/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:00:18 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/20 14:27:23 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	lmeal_mutex(t_data *data, t_input args)
{
	int		i;
	bool	mutex_fail;

	i = -1;
	mutex_fail = false;
	while (++i < args.num_phil)
	{
		if (pthread_mutex_init(&data->philo[i].m_lmeal, NULL))
		{
			mutex_fail = true;
			break ;
		}
	}
	if (mutex_fail == true)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&data->philo[i].m_lmeal);
			i--;
		}
		return (FAIL);
	}
	return (SUCCESS);
}

int	forks_mutex(t_data *data, t_input args)
{
	int		i;
	bool	mutex_fail;

	i = -1;
	mutex_fail = false;
	while (++i < args.num_phil)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL))
		{
			mutex_fail = true;
			break ;
		}
	}
	if (mutex_fail == true)
	{
		while (i >= 0)
			pthread_mutex_destroy(&data->m_forks[i--]);
		return (FAIL);
	}
	return (SUCCESS);
}

int	alloc_mutex(t_data *data)
{
	data->m_alive = malloc(sizeof(pthread_mutex_t));
	data->m_print = malloc(sizeof(pthread_mutex_t));
	data->m_done = malloc(sizeof(pthread_mutex_t));
	if (!data->m_alive || !data->m_print || !data->m_done)
		return (ft_error(ALLOC_ERR, data, true));
	if (pthread_mutex_init(data->m_print, NULL))
		return (FAIL);
	if (pthread_mutex_init(data->m_done, NULL))
	{
		pthread_mutex_destroy(data->m_print);
		return (FAIL);
	}
	if (pthread_mutex_init(data->m_alive, NULL))
	{
		pthread_mutex_destroy(data->m_print);
		pthread_mutex_destroy(data->m_done);
		return (FAIL);
	}
	return (SUCCESS);
}

int	init_mutex(t_data *data, t_input args)
{
	if (lmeal_mutex(data, args))
		return (ft_error(MUTEX_ERR, data, false));
	if (forks_mutex(data, args))
		return (ft_error(MUTEX_ERR, data, true));
	if (alloc_mutex(data))
		return (FAIL);
	return (SUCCESS);
}

void	cleanup_mutex(pthread_mutex_t *ptr)
{
	pthread_mutex_destroy(ptr);
	free_null((void *)ptr);
}
