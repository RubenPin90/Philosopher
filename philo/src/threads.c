/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:42 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/21 17:52:43 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	*start_feast(void *ptr)
{
	t_phil	*philo;

	philo = (t_phil *)ptr;
	pthread_mutex_lock(&philo->m_lmeal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_lmeal);
	if (philo->args.num_phil == 1)
		ft_lonely(philo);
	else
	{
		while (1)
			if (ft_eat_sleep_think(philo))
				break ;
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
			ft_print(&philo[i], RED, DIED, true);
			pthread_mutex_lock(data->m_alive);
			data->alive = false;
			pthread_mutex_unlock(data->m_alive);
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

int	join_threads(t_data *data, int i)
{
	while (i >= 0)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (ft_error(JOIN_ERR, data, true));
		i--;
	}
	return (SUCCESS);
}

int	feast_stop(t_data *data, int i)
{
	pthread_mutex_lock(data->m_print);
	pthread_mutex_lock(data->m_alive);
	data->check_print = true;
	data->alive = false;
	pthread_mutex_unlock(data->m_alive);
	pthread_mutex_unlock(data->m_print);
	join_threads(data, i - 1);
	printf("Creating pthread %d failed!\n", i);
	return (ft_error(PTHREAD_ERR, NULL, false));
}

int	start_threads(t_data *data, t_phil *philo)
{
	int	i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->args.num_phil)
	{
		if (pthread_create(&philo[i].thread, NULL, &start_feast, &philo[i]))
			return (feast_stop(data, i));
		usleep(1000);
	}
	ft_control(data, philo);
	join_threads(data, i - 1);
	return (SUCCESS);
}
