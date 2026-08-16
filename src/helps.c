#include "../includes/codexion.h"


int	ft_strcpy(char *dest, char *src)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(src);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}