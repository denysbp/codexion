/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:05:56 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/11 16:13:17 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"


void	*routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
	return (NULL);
}

int	main(void)
{
	pthread_t t1, t2;
	pthread_mutex_t mutex;
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_mutex_lock(&mutex);
	pthread_join(t1, NULL);
	pthread_mutex_unlock(&mutex);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t2, NULL);
	return (0);
}
