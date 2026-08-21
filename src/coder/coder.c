#include "../../includes/codexion.h"


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
	coder->is_compiling = false;
	coder->has_compiled = false;
	coder->request_time = 0;
	pthread_mutex_init(&coder->mutex, NULL);
	pthread_cond_init(&coder->cond, NULL);
}

void	create_dongle(dongle_t *dongle, int id)
{
	dongle->id = id;
	dongle->free = true;
	dongle->cool_down = 0;
}
long	deadline(coder_t *coder)
{
	if (!coder->has_compiled)
	{
		return (coder->time_to_burnout);
	}
	return (coder->last_compile + coder->time_to_burnout);
}