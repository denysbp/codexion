#include "../../includes/codexion.h"


// coder_t	create_coders(program_t	**program, int id)
// {
// 	coder_t	coder;

// 	coder.id = id;
// 	coder.burned_out = false;
// 	coder.time_to_burnout = (*program)->time_to_burnout;
// 	coder.dongles = 0;
// 	coder.last_compile = 0;
// 	coder.left = &(*program)->dongles[id - 1];
// 	coder.right = &(*program)->dongles[((id - 1) + 1) % (*program)->numbers_coders];
// 	coder.can_run = false;
// 	coder.finished = false;
// 	coder.compile_times = (*program)->numbers_of_compiles;
// 	coder.program = (*program);
// 	pthread_mutex_init(&coder.mutex, NULL);
// 	pthread_cond_init(&coder.cond, NULL);
// 	return (coder);
// }

void	create_coders(program_t	*program,coder_t *coder, int id)
{
	coder->id = id;
	coder->burned_out = false;
	coder->time_to_burnout = program->time_to_burnout;
	coder->dongles = 0;
	coder->last_compile = 0;
	coder->left = &program->dongles[id - 1];
	coder->right = &program->dongles[((id - 1) + 1) % program->numbers_coders];
	coder->can_run = false;
	coder->finished = false;
	coder->compile_times = program->numbers_of_compiles;
	coder->program = program;
	pthread_mutex_init(&coder->mutex, NULL);
	pthread_cond_init(&coder->cond, NULL);
}


// dongle_t	create_dongles(int id)
// {
// 	dongle_t	dongle;

// 	dongle.id = id;
// 	dongle.free = true;
// 	return (dongle);
// }

void	create_dongle(dongle_t *dongle, int id)
{
	dongle->id = id;
	dongle->free = true;
}
long	deadline(coder_t *coder)
{
	return (coder->last_compile + coder->time_to_burnout);
}