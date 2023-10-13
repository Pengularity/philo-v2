/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:38:05 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/13 16:39:09 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	current_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_sleep(long int time_in_ms)
{
	long int	start_time;
	long int	elapsed_time;

	start_time = current_time();
	elapsed_time = 0;
	while (elapsed_time < time_in_ms)
	{
		if (time_in_ms - elapsed_time > 100)
			usleep(10 * 1000);
		else
			usleep((time_in_ms - elapsed_time) * 1000);
		elapsed_time = current_time() - start_time;
	}
}

int	ft_error(char *str)
{
	ft_putstr_fd(RED "Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET "\n", 2);
	return (0);
}
