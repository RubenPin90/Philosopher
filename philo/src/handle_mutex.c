/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:00:18 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/18 11:30:35 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int lmeal_mutex(t_data *data, t_input args)
{
	bool	mutex_fail;

	mutex_fail = false;
	while (++i < data->args.num_phil)
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
int alloc_mutex(t_data *data)
{
	data->write = malloc(sizeof(pthread_mutex_t));
	if (!data->write)
		return (FAIL);
	data->m_done = malloc(sizeof(pthread_mutex_t));
	if (!data->m_done)
	{
		free_null(data->write);
		return (FAIL);
	}
	data->m_alive = malloc(sizeof(pthread_mutex_t));
	if (!data->m_alive)
	{
		free_null(data->write);
		free_null(data->m_done);
		return (FAIL);
	}
	return (SUCCESS);
}



int	mutex_init(t_data *data, t_input args)
{
	if (lmeal_mutex(data, data->args))
		return ()
	alloc_mutex(data);
	if (pthread_mutex_init(data->write, NULL))
		return (ft_error(MUTEX_ERR, data, args.num_phil));
	if (pthread_mutex_init(data->m_done, NULL))
		return (ft_error(MUTEX_ERR, data, args.num_phil));
	if (pthread_mutex_init(data->m_alive, NULL))
		return (ft_error(MUTEX_ERR, data, args.num_phil));
	return (SUCCESS);
}
