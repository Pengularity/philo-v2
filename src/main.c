/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:06:39 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/13 18:19:17 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	cleanup(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_destroy(&args->philo[i].left_fork);
		if (args->philo[i].right_fork != NULL)
		{
			pthread_mutex_destroy(args->philo[i].right_fork);
			free(args->philo[i].right_fork);
		}
		i++;
	}
	pthread_mutex_destroy(&args->death_mutex);
	pthread_mutex_destroy(&args->time_to_eat_mutex);
	pthread_mutex_destroy(&args->finish_eating_mutex);
	pthread_mutex_destroy(&args->print_mutex);
	if (args->num_philo_finished_eating == args->num_philo)
		printf(BRIGHT_GREEN
			"All philosophersate the number of required times\n");
	free(args->philo);
}

int	main(int ac, char **av)
{
	t_args		args;

	if (!(parse_args(ac, av, &args)))
		return (ft_error("Invalid arguments"));
	args.philo = malloc(sizeof(t_philo) * args.num_philo);
	if (!args.philo)
		return (ft_error("Failed to Malloc"));
	if (!(initialize(&args)))
		return (free(args.philo), ft_error("Failed to initialize threads"));
	if (!(start_simulation(&args)))
		return ((cleanup(&args), ft_error("Failed to start simulation")));
	cleanup(&args);
	return (0);
}
