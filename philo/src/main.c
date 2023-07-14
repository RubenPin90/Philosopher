/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:32 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/12 16:15:48 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		res;

	res = 0;
	if (argc < 5 || argc > 6)
		return (ft_error(INPUT_ERR1, NULL));
	if (check_args(argc - 1, &argv[1]))
		return (ft_error(INPUT_ERR2, NULL));
	if (start_init(&data, &argv[1], argc - 1))
		return (FAIL);
	res = start_threads(&data, data.philo);
	ft_exit(&data);
	return (res);
}