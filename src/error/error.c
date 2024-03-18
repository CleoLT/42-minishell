#include "minishell.h"

void	ft_error(char *arg, int exit_code)
{
	perror(arg);
	exit(exit_code);
}
