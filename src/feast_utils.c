/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:38:19 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/27 14:04:02 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	is_dead(t_phil *philo)
{	
	int	tmp;

	tmp = false;
	pthread_mutex_lock(&philo->m_lmeal);
	pthread_mutex_lock(&philo->m_full);
	if ((get_time() - philo->last_meal) > philo->args.time_to_die && \
														philo->full != true)
		tmp = true;
	pthread_mutex_unlock(&philo->m_lmeal);
	pthread_mutex_unlock(&philo->m_full);
	return (tmp);
}

int	are_full(t_data *data)
{
	int	tmp;

	tmp = false;
	if (data->args.phil_hunger < 0)
		return (false);
	pthread_mutex_lock(&data->m_done);
	if (data->done == data->args.num_phil)
		tmp = true;
	pthread_mutex_unlock(&data->m_done);
	return (tmp);
}

int	ft_print(t_phil *philo, char *color, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->write);
	timestamp = get_time() - philo->data->start_time;
	if (*philo->check_print == false)
		printf("%s%lld\t%d %s%s\n", color, timestamp, philo->id, msg, RESET);
	if (is_dead(philo) == true)
		*philo->check_print = true;
	pthread_mutex_unlock(&philo->data->write);
	return (SUCCESS);
}

int	check_status(t_phil *philo, bool check)
{
	int	tmp;

	tmp = false;
	pthread_mutex_lock(&philo->data->m_alive);
	if (philo->data->alive == false)
		tmp = true;
	pthread_mutex_unlock(&philo->data->m_alive);
	if (tmp && check)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	}
	return (tmp);
}