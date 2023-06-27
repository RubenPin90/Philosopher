/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:51:31 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/27 23:41:14 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	*start_the_feast(void *ptr)
{
	t_phil	*philo;

	philo = (t_phil *)ptr;
	pthread_mutex_lock(&philo->m_lmeal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_lmeal);
	while (philo->meals != philo->args.phil_hunger)
	{
		if (ft_eat_sleep_think(philo))
			break ;
	}
	if (philo->meals == philo->args.phil_hunger)
	{
		pthread_mutex_lock(&philo->m_full);
		philo->full = true;
		pthread_mutex_unlock(&philo->m_full);
		pthread_mutex_lock(&philo->data->m_done);
		philo->data->done++;
		pthread_mutex_unlock(&philo->data->m_done);
	}
	return (NULL);
}

void	ft_control(t_data *data, t_phil *philo)
{
	int	i;

	i = 0;
	while (i <= data->args.num_phil)
	{
		if (i == data->args.num_phil)
			i = 0;
		if (is_dead(&philo[i]))
		{
			ft_print(&philo[i], RED, DIED);
			pthread_mutex_lock(&data->m_alive);
			data->alive = false;
			pthread_mutex_unlock(&data->m_alive);
			return ;
		}
		if (are_full(data))
		{
			printf("All philos are full!\n");
			return ;
		}
		i++;
	}
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_phil && data->philo[i].thread)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (SUCCESS);
}

int	start_threads(t_data *data, t_phil *philo)
{
	int	i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->args.num_phil)
	{
		if (pthread_create(&philo[i].thread, NULL, \
									&start_the_feast, &philo[i]))
		{
			printf("Creating pthread with ID %d failed!", i);
			return (FAIL);
		}
		usleep(1000);
	}
	ft_control(data, philo);
	join_threads(data);
	return (SUCCESS);
}
