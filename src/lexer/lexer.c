#include "minishell.h"
/*
static char **split_line(char *str)
{




}
*/
void	lexer_token(char *line)
{
	char	**value;
	int		i;
	
//	(*token)->type = PIPE;
	value = ft_split(line, ' ');
	i = 0;
	while (value[i])
	{
		//append_token(token, value[i]); 
		printf("%s\n", value[i]);
		i++;
	}

}
