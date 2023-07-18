/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:56 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/18 11:50:34 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	init_data(t_data **data, char **av, int count)
{
	*data = malloc(sizeof(t_data) * 1);
	if (!*data)
		return (ft_error(ALLOC_ERR, NULL, false));
	memset(*data, 0, sizeof(t_data));
	(*data)->args.num_phil = ft_atoi(av[0]);
	(*data)->args.time_to_die = ft_atoi(av[1]);
	(*data)->args.time_to_eat = ft_atoi(av[2]);
	(*data)->args.time_to_sleep = ft_atoi(av[3]);
	if (count == 5)
		(*data)->args.phil_hunger = ft_atoi(av[4]);
	else
		(*data)->args.phil_hunger = -1;
	(*data)->alive = 1;
	if (!(*data)->args.num_phil || !(*data)->args.time_to_die || \
		!(*data)->args.time_to_eat || !(*data)->args.time_to_sleep || \
		(!(*data)->args.phil_hunger && count == 5))
		return (FAIL);
	return (SUCCESS);
}

int	init_forks(t_data *data, t_input args)
{
	int		i;
	bool	mutex_fail;

	data->forks = malloc(sizeof(pthread_mutex_t) * args.num_phil);
	if (!data->forks)
		return (ft_error(ALLOC_ERR, data, false));
	memset(data->forks, 0, sizeof(pthread_mutex_t) * args.num_phil);
	i = -1;
	mutex_fail = false;
	while (++i < args.num_phil)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			mutex_fail = true;
			break;
		}
	}
	if (mutex_fail == true)
	{
		while (i >= 0)
			pthread_mutex_destroy(&data->forks[i--]);
		return (ft_error(MUTEX_ERR, data, false));
	}
	return (SUCCESS);
}

int	init_philos(t_data *data, t_input args)
{
	data->philo = malloc(sizeof(t_phil) * args.num_phil);
	if (!data->philo)
		return (ft_error(ALLOC_ERR, data, args.num_phil));
	memset(data->philo, 0, sizeof(t_phil) * args.num_phil);
	fill_philos(data, data->philo, args);
	if (mutex_init(data, data->args))
		return (FAIL);
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

int	start_init(t_data **data, char **av, int count)
{
	if (init_data(data, av, count))
		return (ft_error(INIT_ERR, *data, (*data)->args.num_phil));
	if (init_forks(*data, (*data)->args))
		return (FAIL);
	if (init_philos(*data, (*data)->args))
		return (FAIL);
	return (SUCCESS);
}
