/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:21:01 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/15 19:34:02 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	handle_philosopher_action(t_philo *philo, t_args *args, int is_dead)
{
	if (is_dead)
	{
		print_status(philo, args, RED, "died");
		args->someone_has_died = 1;
		pthread_mutex_unlock(&args->meal_mutex);
	}
	else
	{
		pthread_mutex_lock(&args->finish_eating_mutex);
		philo->has_finished_eating = 1;
		args->num_philo_finished_eating++;
		pthread_mutex_unlock(&args->meal_mutex);
		pthread_mutex_unlock(&args->finish_eating_mutex);
	}
}

void	*monitor(void *philo_void)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)philo_void;
	args = philo->args;
	while (1)
	{
		pthread_mutex_lock(&args->meal_mutex);
		if (current_time() - philo->last_meal_time > args->time_to_die)
		{
			handle_philosopher_action(philo, args, 1);
			break ;
		}
		if (philo->times_eaten >= args->nb_must_eat)
		{
			handle_philosopher_action(philo, args, 0);
			break ;
		}
		pthread_mutex_unlock(&args->meal_mutex);
		usleep(1000);
	}
	return (NULL);
}


void	*thread(t_philo *philo, t_args *args)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, &monitor, (void *)philo);
	pthread_detach(monitor_thread);
	philosopher_routine(philo, args);
	return (NULL);
}

void	*start_simulation(t_args *args)
{
	int		i;

	i = 0;
	while (i < args->num_philo)
	{
		if (pthread_create(&args->philo[i].thread_id,
				NULL, philosopher_routine, &args->philo[i]) != 0)
			return (ft_error("Failed to create thread"), 0);
		i++;
	}

	i = 0;
	while (i < args->num_philo)
	{
		pthread_join(args->philo[i].thread_id, NULL);
		i++;
	}

	return (1);
}
