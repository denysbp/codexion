/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:05:56 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/11 21:54:43 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

pthread_mutex_t mutex;



void	*routine(void *str)
{
	int *numero;
	numero = (int *)str;
	pthread_mutex_lock(&mutex);
	if (*(numero) == 10000)
	{
		*(numero) -= 10000;
		pthread_mutex_unlock(&mutex);
		printf("Eu ganhei\n");
	}
	else
		printf("Eu perdi\n");
	return (NULL);
}

int	main(void)
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	int primo;
	primo = 10000;
	pthread_create(&t1, NULL, &routine, &primo);
	pthread_create(&t2, NULL, &routine, &primo);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return (0);
}
