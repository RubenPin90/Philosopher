/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:36:02 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/27 23:50:16 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	init_data(t_data *data, char **av, int count)
{
	data->args.num_phil = ft_atoi(av[0]);
	data->args.time_to_die = ft_atoi(av[1]);
	data->args.time_to_eat = ft_atoi(av[2]);
	data->args.time_to_sleep = ft_atoi(av[3]);
	if (count == 5)
		data->args.phil_hunger = ft_atoi(av[4]);
	else
		data->args.phil_hunger = -1;
	data->alive = 1;
	data->done = 0;
	data->check_print = 0;
	data->n_thread = 0;
	if (!data->args.num_phil || !data->args.time_to_die || \
		!data->args.time_to_eat || !data->args.time_to_sleep || \
		(!data->args.phil_hunger && count == 5))
		return (FAIL);
	return (SUCCESS);
}

int	init_forks(t_data *data, t_input args)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * args.num_phil);
	if (!data->forks)
		return (ft_error(ALLOC_ERR, NULL));
	memset(data->forks, 0, sizeof(pthread_mutex_t) * args.num_phil);
	i = -1;
	while (++i < args.num_phil)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error(MUTEX_ERR, data));
	if (pthread_mutex_init(&data->write, NULL))
		return (ft_error(MUTEX_ERR, data));
	if (pthread_mutex_init(&data->m_done, NULL))
		return (ft_error(MUTEX_ERR, data));
	if (pthread_mutex_init(&data->m_alive, NULL))
		return (ft_error(MUTEX_ERR, data));
	return (SUCCESS);
}

int	init_philos(t_data *data, t_input args)
{
	int	i;

	data->philo = malloc(sizeof(t_phil) * args.num_phil);
	if (!data->philo)
		return (ft_error(ALLOC_ERR, data));
	memset(data->philo, 0, sizeof(t_phil) * args.num_phil);
	fill_philos(data, data->philo, args);
	i = -1;
	while (++i < data->args.num_phil)
	{
		if (pthread_mutex_init(&data->philo[i].m_lmeal, NULL))
			return (ft_error(MUTEX_ERR, data));
		if (pthread_mutex_init(&data->philo[i].m_full, NULL))
			return (ft_error(MUTEX_ERR, data));
	}
	return (SUCCESS);
}

void	fill_philos(t_data *data, t_phil *philo, t_input args)
{
	int	i;

	i = 0;
	while (i < args.num_phil)
	{
		philo[i].data = data;
		philo[i].args = args;
		philo[i].full = false;
		philo[i].check_print = &data->check_print;
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].last_meal = 0;
		philo[i].l_fork = i;
		philo[i].r_fork = i - 1;
		i++;
	}
	philo[0].r_fork = args.num_phil - 1;
}

int	start_init(t_data *data, char **av, int count)
{
	if (init_data(data, av, count))
		return (ft_error(INIT_ERR, NULL));
	if (init_forks(data, data->args))
		return (FAIL);
	if (init_philos(data, data->args))
		return (FAIL);
	return (SUCCESS);
}
