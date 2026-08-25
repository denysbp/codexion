/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:18:18 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/25 16:20:55 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <pthread.h>

typedef struct t_error
{
	char	*str;
}			t_error;

typedef struct t_dongle
{
	int				id;
	bool			free;
	long			cool_down;
}					t_dongle;

typedef struct t_program	t_program;
typedef struct t_heap		t_heap;

typedef struct t_coder
{
	pthread_t		coder;
	t_dongle		*left;
	t_dongle		*right;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex;
	t_program		*program;

	long			time_to_burnout;
	long			last_compile;
	long			request_order;
	int				id;
	int				compile_times;
	int				dongles;
	bool			burned_out;
	bool			can_run;
	bool			finished;
	bool			has_compiled;
	bool			is_compiling;
}					t_coder;

typedef struct t_program
{
	int				numbers_coders;
	int				numbers_of_compiles;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			dongle_cooldown;
	long			start_time;
	long			request_counter;

	pthread_mutex_t	mutex_state;
	pthread_t		monitor;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	mutex_dongle;
	pthread_cond_t	cond_dongles;
	pthread_mutex_t	mutex_print;
	t_heap			*wait_heap;

	bool			runnig;
	char			*scheduler;
}					t_program;

typedef struct t_heap
{
	t_coder			**coders;
	int				size;
	int				capacity;
	char			*scheduler;
	pthread_mutex_t	mutex;
}					t_heap;

struct timespec	get_timeout(long timestamp);

#endif