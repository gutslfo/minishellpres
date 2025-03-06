#include "../minishell.h"

char    *copy_token(char *source, char *dest, token_type type)
{
	int	i;

	i = 0;
	while (source[i++])
	{
		switch (type)
		{
			case WORD:
			while (is_command_char(source[i]))
				dest[i] = source[i];
		}
	}
	return (dest);
}
