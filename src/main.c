/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:01:36 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/27 15:07:46 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(INPUT_ERR1, NULL));
	if (check_args(argc - 1, &argv[1]))
		return (ft_error(INPUT_ERR2, NULL));
	if (start_init(&data, &argv[1], argc - 1))
		return (FAIL);
	if (data.args.num_phil == 1)
	{
		if (ft_lonely_philo(&data, data.philo))
			return (FAIL);
	}
	else
	{
		if (start_threads(&data, data.philo))
			return (FAIL);
	}
	ft_exit(&data);
	return (SUCCESS);
}
