#include "../includes/codexion.h"


char	*ft_strcpy(char *src)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = strlen(src);
	dest = malloc(sizeof(char) * len);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
