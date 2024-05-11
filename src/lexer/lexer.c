#include "minishell.h"
#include "lexer.h"

void	lexer_token(t_tools *tools, char *line)
{
	tools->str = ft_strtrim(line, " ");
	if (!tools->str)
		ft_error("exit", errno);
	if (!token_reader(tools))
		ft_error("bad lexer", errno);
	if (!expander_reader(tools))
		ft_error("bad expander", errno);
/*	if (tools->str[0] == '\0')
		return (free_tools(tools));*/
}
