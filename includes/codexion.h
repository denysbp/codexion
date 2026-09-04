/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:49:39 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/04 20:19:24 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include "structs.h"
# include <limits.h>
# define CODERS 1
# define TIME_BURNOUT 2
# define TIME_COMPILE 3
# define TIME_DEBUG 4
# define TIME_REFACTOR 5
# define NUMBER_COMPILES 6
# define DONGLE_COOLDOWN 7
# define SCHEDULER 8
# define ERROR -1

bool			invalid_numbers(const char *str);
bool			signal(char c);
bool			args_validation(t_error *error, t_program *program);
bool			is_stoping(t_coder **coder);
bool			is_running(t_program *program);
bool			monitoring_flow(t_program **program, long now);
bool			has_higher_priority_waiter(t_heap *heap, t_coder *coder);
bool			coder_shares_dongle(t_coder *a, t_coder *b);
bool			is_blocked(t_program *program, t_coder **coder);
bool			has_compiles(t_coder *coder);

int				parser(const char *numbers_coders, t_error **error);
int				has_priority(t_coder *coder_a,
					t_coder *coder_b, char *scheduler);

int				scheduler(t_program *program);
int				save_args(char **argv, t_program **program, t_error *error);

long			parser_long(const char *numbers_coders, t_error **error);
long			deadline(t_coder *coder);
long			get_time(void);

void			take_dongle(t_coder **coder);
void			release_dongle(t_coder **coder);
void			compiling(t_coder **coder);
void			debugging(t_coder **coder);
void			refactoring(t_coder **coder);
void			*burnout_monitoring(void *arg);
void			print_save(t_program *pg, char *str, int id);
void			wake_up(t_program **program);
void			flow(t_coder **coder);
void			join_pthread(t_program **program);
void			routine_flow(t_coder **coder);
void			burnout(t_program **program, t_coder *coder);
void			heap_remove(t_heap *heap, t_coder *coder);

t_program		*generator_engine(char **argv, t_error *error);
t_heap			*heap_init(int capacity, char *scheduler, t_program **program);
t_coder			*heappop(t_heap **heap);
t_heap			*wait_heap_init(int capacity, char *scheduler);

void			create_coders(t_program	*program, t_coder *coder, int id);
void			create_dongle(t_dongle *dongle, int id);
void			free_engine(t_program *program);
void			heapfy(t_heap **heap, int i);
void			heappush(t_heap	**heap, t_coder	*coder);
void			swap(t_coder **coder_a, t_coder **coder_b);
void			free_heap(t_heap *heap);
void			*coder_routine(void *arg);
void			program_usage(void);
void			create_objects(t_program **program);
void			cond_selector(t_coder *coder);
void			print(t_error error);
void			sucess(t_coder **coder);


char			*error_message(const char *str);
char			*ft_strcpy(char *src);

#endif