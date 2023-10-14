/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:28:01 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/14 18:15:47 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_num(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > ' 9')
			return (0);
		i++;
	}
	return (i > 0);
}

int	parse_args(int ac, char **av, t_args *args)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_num(av[i]))
			return (0);
		i++;
	}
	args->num_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->max_meals = -1;
	if (ac == 6)
		args->max_meals = ft_atoi(av[5]);
	if (args->num_philo <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0
		|| (ac == 6 && args->max_meals <= 0))
		return (0);
	return (1);
}

static int	init_mutexes(t_args *args)
{
	if (pthread_mutex_init(&args->print_mutex, NULL)
		||pthread_mutex_init(&args->death_mutex, NULL)
		||pthread_mutex_init(&args->time_to_eat_mutex, NULL)
		||pthread_mutex_init(&args->finish_eating_mutex, NULL))
		return (0);
	return (1);
}

static int	init_philosophers(t_args *args, int i)
{
	args->philo[i].id = i + 1;
	args->philo[i].times_eaten = 0;
	args->philo[i].last_meal_time = args->start_time;
	args->philo[i].has_finished_eating = 0;
	if (pthread_mutex_init(&args->philo[i].left_fork, NULL))
		return (0);
	if (i == args->num_philo)
		args->philo[i].right_fork = &args->philo[0].left_fork;
	else
		args->philo[i].right_fork = &args->philo[i + 1].left_fork;
	return (1);
}

int	initialize(t_args *args)
{
	int	i;

	args->philo = malloc(sizeof(t_philo) * args->num_philo);
	if (!args->philo || !init_mutexes(args))
		return (0);
	i = 0;
	args->stop_flag = 0;
	args->someone_has_died = 0;
	args->num_philo_finished_eating = 0;
	args->start_time = current_time();
	while (i < args->num_philo)
	{
		if (!init_philosophers(args, i))
			return (0);
		i++;
	}
	return (1);
}
