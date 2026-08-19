#include "../includes/codexion.h"


char	*ft_strcpy(char *src)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = strlen(src);
	dest = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}


struct timespec	get_timeout(long timestamp)
{
	struct timespec	ts;

	ts.tv_sec = timestamp / 1000;
	ts.tv_nsec = (timestamp % 1000) * 1000000L;
	return (ts);
}

void	program_usage()
{
	printf("usage: ./codexion ");
	printf("<coders> <burnout> <compile> ");
	printf("<debug> <refactor> <compile times> <cooldown> <scheduler>\n");
	printf("\n");
	printf("Arguments:\n");
	printf("\tcoders         | numbers of coder; >= 1\n");
	printf("\tburnout        | ms until the coder burnout; >= 0\n");
	printf("\tcompile        | ms spent compiling; >= 0\n");
	printf("\tdebug          | ms spent debugging; >= 0\n");
	printf("\trefactor       | ms spent refactoring; >= 0\n");
	printf("\tcompile time   | compiles per code before simulation ends; >= 1\n");
	printf("\tcooldown       | ms for a dongle to become available; >= 0\n");
	printf("\tscheduler      | type of scheduler, fifo or edf\n");
}