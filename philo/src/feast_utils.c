/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:08:12 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/21 17:52:05 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	is_dead(t_phil *philo)
{
	int	tmp;

	tmp = false;
	pthread_mutex_lock(&philo->m_lmeal);
	if ((get_time() - philo->last_meal) > philo->args.time_to_die)
		tmp = true;
	pthread_mutex_unlock(&philo->m_lmeal);
	return (tmp);
}

int	are_full(t_data *data)
{
	int	tmp;

	tmp = false;
	if (data->args.phil_hunger < 0)
		return (false);
	pthread_mutex_lock(data->m_done);
	if (data->done == data->args.num_phil)
		tmp = true;
	pthread_mutex_unlock(data->m_done);
	return (tmp);
}

int	ft_print(t_phil *philo, char *color, char *msg, bool vip)
{
	long long	timestamp;

	pthread_mutex_lock(philo->data->m_print);
	timestamp = get_time() - philo->data->start_time;
	if (are_full(philo->data) == true)
		*philo->check_print = true;
	if (*philo->check_print == false || vip == true)
		printf("%s%lld\t%d %s%s\n", color, timestamp, philo->id, msg, RESET);
	if (is_dead(philo) == true || are_full(philo->data) == true)
		*philo->check_print = true;
	pthread_mutex_unlock(philo->data->m_print);
	return (SUCCESS);
}

int	check_status(t_phil *philo)
{
	int	tmp;

	tmp = false;
	pthread_mutex_lock(philo->data->m_alive);
	if (philo->data->alive == false)
		tmp = true;
	pthread_mutex_unlock(philo->data->m_alive);
	if (are_full(philo->data))
		tmp = true;
	return (tmp);
}

int	update_meals(t_phil *philo, t_input args, t_data *data)
{
	philo->meals++;
	if (philo->meals == args.phil_hunger)
	{
		pthread_mutex_lock(data->m_done);
		data->done++;
		pthread_mutex_unlock(data->m_done);
	}
	return (SUCCESS);
}
