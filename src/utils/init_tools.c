/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:56:36 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 15:10:49 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_shlvl(t_envp **envp)
{
	t_envp	*env;
	int		num;

	env = *envp;
	while (env)
	{
		if (!ft_strncmp(env->name, "SHLVL", 6) && env->value)
		{
			num = ft_atoi(env->value);
			if (num < 0)
				num = -1;
			if (num > 999)
				num = 0;
			if (num == 999)
			{
				exec_export(ft_strdup("SHLVL"), "", REPLACE_MODE, envp);
				return ;
			}
			num++;
			exec_export(ft_strdup("SHLVL"), ft_itoa(num), REPLACE_MODE, envp);
			return ;
		}
		env = env->next;
	}
	envp_addnode("SHLVL", "1", envp);
}

int	tools_init(t_tools *tools, char **envp)
{
	tools->envp = ft_arrdup(envp);
	tools->str = NULL;
	tools->envp_list = NULL;
	tools->lexer_list = NULL;
	tools->exit_code = 0;
	if (!envp_reader(tools))
		ft_error("bad envp_reader", errno);
	delete_env(&tools->envp_list, "OLDPWD");
	envp_addnode("OLDPWD", NULL, &tools->envp_list);
	export_shlvl(&tools->envp_list);
	ft_signals(PROCESS_OFF);
	rl_catch_signals = 0;
	return (1);
}

void	init_tools_loop(t_tools *tools)
{
	tools->path = get_path(*tools);
	tools->cmd = NULL;
	tools->built_type = 0;
	g_exit_code = 0;
	tools->stdin_fd = dup(STDIN_FILENO);
	tools->stdout_fd = dup(STDOUT_FILENO);
}
