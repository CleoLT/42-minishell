#include "minishell.h"
#include "lexer.h"

void	lexer_token(t_tools *tools, char *line)
{
	char	*tmp;

	tools->str = line;
	tmp = ft_strtrim(tools->str, " ");
	free(tools->str);
	tools->str = tmp;
	printf("%s\n", tools->str);
	if (!tools->str)
		ft_error("exit", errno);
	if (!token_reader(tools))
		ft_error("bad lexer", errno);
/*	if (tools->str[0] == '\0')
		return (free_tools(tools));*/
}
