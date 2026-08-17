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