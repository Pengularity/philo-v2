/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:28:15 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/14 18:16:22 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define WHITE "\033[97m"
# define RED "\033[91m"
# define GREEN "\033[92m"
# define BLUE "\033[94m"
# define YELLOW "\033[93m"
# define BRIGHT_GREEN "\033[92m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int							id;
	int							times_eaten;
	int							last_meal_time;
	int							has_finished_eating;
	pthread_t					left_fork;
	pthread_t					*right_fork;
}								t_philo;

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				stop_flag;
	int				someone_has_died;
	int				num_philo_finished_eating;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_to_eat_mutex;
	pthread_mutex_t	finish_eating_mutex;
	t_philo			*philo;
}					t_args;

void	print_status(t_philo *philo, t_args *args, char *color, char *status);
void	*philosopher_routine(t_philo *philo, t_args *args);
int		ft_error(char *str);
void	ft_sleep(long int time_in_ms);
long	current_time(void);
int		parse_args(int ac, char **av, t_args *args);
int		initialize(t_args *args);


#endif