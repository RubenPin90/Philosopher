/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:10:09 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/12 13:37:09 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	drop_forks(t_data *data, t_phil *philo, int order)
{
	if (order == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
	}
	else if (order == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
	}
	ft_print(philo, BLUE, SLEEP);
	if (check_status(philo, false))
		return (FAIL);
	usleep(philo->args.time_to_sleep * 1000);
	ft_print(philo, GREEN, THINK);
	return (SUCCESS);
}

/*look at fork and if its available pick it up.
*/
int	pick_up_forks(t_data *data, t_phil *philo, int order)
{
	if (order == 0)
	{
		pthread_mutex_lock(&data->forks[philo->r_fork]);
		pthread_mutex_lock(&data->forks[philo->l_fork]);
	}
	else if (order == 1)
	{
		pthread_mutex_lock(&data->forks[philo->l_fork]);
		pthread_mutex_lock(&data->forks[philo->r_fork]);
	}
	ft_print(philo, YELLOW, FORK);
	ft_print(philo, YELLOW, FORK);
	return (SUCCESS);
}

int	ft_eat_sleep_think(t_phil *philo)
{
	if (check_status(philo, false))
		return (FAIL);
	pick_up_forks(philo->data, philo, philo->id % 2);
	pthread_mutex_lock(&philo->m_lmeal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_lmeal);
	ft_print(philo, GREEN, EAT);
	usleep(philo->args.time_to_eat * 1000);
	philo->meals++;
	drop_forks(philo->data, philo, philo->id % 2);
	return (SUCCESS);
}

int	ft_lonely_philo(t_data *data, t_phil *philo)
{
	data->start_time = get_time();
	philo->last_meal = data->start_time;
	ft_print(philo, YELLOW, FORK);
	usleep(philo->args.time_to_die * 1000);
	ft_print(philo, RED, DIED);
	return (SUCCESS);
}
