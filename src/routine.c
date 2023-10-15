/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:18:36 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/15 19:31:10 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_status(t_philo *philo, t_args *args, char *color, char *status)
{
	long	time;

	time = current_time() - args->start_time;
	pthread_mutex_lock(&args->print_mutex);
	printf("%ld %d %s%s%s\n", time, philo->id, color, status, RESET);
	pthread_mutex_unlock(&args->print_mutex);
}

void	eat(t_philo *philo, t_args *args)
{
	if (philo->id == args->num_philo)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	print_status(philo, args, WHITE, "has taken a fork");
	print_status(philo, args, GREEN, "is eating");
	pthread_mutex_lock(&args->meal_mutex);
	gettimeofday(&philo->last_meal_time, NULL);
	pthread_mutex_unlock(&args->meal_mutex);
	ft_sleep(args->time_to_eat);
	pthread_mutex_lock(&args->meal_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&args->meal_mutex);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo, t_args *args)
{
	print_status(philo, args, BLUE, "is sleeping");
	ft_sleep(args->time_to_sleep);
	print_status(philo, args, YELLOW, "is thinking");
}

void	*philosopher_routine(t_philo *philo, t_args *args)
{
	if (philo->id % 2 == 0)
		usleep(args->time_to_eat / 10);
	while (!is_dead(philo) && !philo->has_finished_eating)
	{
		eat(philo, args);
		sleep_and_think(philo, args);
		// if (args->nb_must_eat != 0 && philo->times_eaten >= args->nb_must_eat)
		// {
		// 	pthread_mutex_lock(&args->finish_eating_mutex);
		// 	philo->has_finished_eating = 1;
		// 	args->num_philo_finished_eating++;
		// 	pthread_mutex_unlock(&args->finish_eating_mutex);
		// }
	}
}
