/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:28:15 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/13 17:56:45 by wnguyen          ###   ########.fr       */
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
	int							last_meal_time;
	int							times_eaten;
	int							has_finished_eating;
	t_fork						left_fork;
	t_fork						*right_fork;
}								t_philo;

typedef struct s_args
{
	int				num_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				stop_flag;
	int				max_meals;
	int				someone_has_died;
	int				num_philo_finished_eating;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_to_eat_mutex;
	pthread_mutex_t	finish_eating_mutex;
	t_philo			*philo;
}					t_args;

#endif