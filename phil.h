/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:01:53 by rubsky            #+#    #+#             */
/*   Updated: 2023/06/27 16:27:54 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

/*Error Flags*/
# define INPUT_ERR1 "Not enough arguments. Expected 4 [5]:\nUsage: \
./philo <num of philos> <die time> <eat time> <sleep time> [meals per philo]"
# define INPUT_ERR2 "Invalid input"
# define INIT_ERR "Error with initializing data"
# define ALLOC_ERR "Malloc error detected"
# define MUTEX_ERR "Error with mutex init"
# define TIME_ERR "Time error"

/*bool*/
# define SUCCESS 0
# define FAIL 1

/*colors*/
# define RESET "\e[0m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define PINK "\e[0;35m"

/*Messages*/
# define EAT "is eating 🍝"
# define SLEEP "is sleeping 😴"
# define THINK "is thinking 🧠"
# define FORK "has taken a fork 🍴"
# define DROP "dropped his forks 🫳"
# define DIED "died 💀"

struct	s_data;

typedef struct s_input
{
	int			num_phil;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			phil_hunger;
}	t_input;

typedef struct s_phil
{
	pthread_t		thread;
	struct s_data	*data;
	t_input			args;	
	int				id;
	int				meals;
	bool			full;
	bool			*check_print;
	pthread_mutex_t	m_full;
	long long		last_meal;
	pthread_mutex_t	m_lmeal;
	int				r_fork;
	int				l_fork;
}	t_phil;

typedef struct s_data
{
	t_input			args;
	t_phil			*philo;
	int				n_thread;
	long long		start_time;
	bool			alive;
	pthread_mutex_t	m_alive;
	int				done;
	pthread_mutex_t	m_done;
	pthread_mutex_t	*forks;
	bool			check_print;
	pthread_mutex_t	write;
}	t_data;

/*init*/
int			start_init(t_data *data, char **av, int count);
void		fill_philos(t_data *data, t_phil *philo, t_input args);
int			init_philos(t_data *data, t_input args);
int			init_forks(t_data *data, t_input args);
int			init_data(t_data *data, char **av, int count);

/*utils*/
int			ft_atoi(char *str);
int			check_args(int count, char **argv);
void		print_data(t_input args);
long long	get_time(void);

/*threads*/
int			start_threads(t_data *data, t_phil *philo);
int			join_threads(t_data *data);

/*exit*/
int			ft_error(char *flag, t_data *data);
void		ft_exit(t_data *data);

/*feast*/
int			ft_eat_sleep_think(t_phil *philo);
int			ft_lonely_philo(t_data *data, t_phil *philo);

/*feast_utils*/
int			is_dead(t_phil *philo);
int			are_full(t_data *data);
int			ft_print(t_phil *philo, char *color, char *msg);
int			check_status(t_phil *philo, bool check);

#endif