/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:16:30 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/24 15:20:46 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cdm_list(t_cmd *cmd)
{
	int i;
	while (cmd)
	{
		if (cmd->infile)
		{
			i = 0;
			while (cmd->infile[i])
			{
				if (cmd->infile[i][1])
					printf("<<%s ", cmd->infile[i][0]);
				else
					printf("<%s ", cmd->infile[i][0]);
				i++;
			}
		}
		if (cmd->outfile)
		{
			i = 0;
			while (cmd->outfile[i])
			{
				if (cmd->outfile[i][1])
					printf(">>%s ", cmd->outfile[i][0]);
				else
					printf(">%s ", cmd->outfile[i][0]);
				i++;
			}
		}
		i = 0;
		while (cmd->arg[i])
			printf("%s ", cmd->arg[i++]);
		if (cmd->next)
			printf("| ");
		else
			printf("\n");
		cmd = cmd->next;
	}
}

void cmd_faker(t_tools *tools, char *line)
{
	t_cmd *comm;
	comm = malloc(sizeof(t_cmd));
	comm->arg = ft_split(line, ' ');
	tools->cmd = comm;
	tools->cmd->infile = NULL;
	tools->cmd->outfile = NULL;
/*	tools->cmd->infile = malloc(sizeof(char *) * 5);
	tools->cmd->infile[0] = malloc(sizeof(char *) * 2);
	tools->cmd->infile[1] = malloc(sizeof(char *) * 3);
	tools->cmd->infile[1] = NULL;
	tools->cmd->infile[2] = malloc(sizeof(char *) * 2);
	tools->cmd->infile[3] = malloc(sizeof(char *) * 3);
	tools->cmd->infile[4] = NULL;
	tools->cmd->infile[0][0] = "outnew";
	tools->cmd->infile[0][1] = NULL;
//	tools->cmd->infile[1][0] = "LOL";
//	tools->cmd->infile[1][1] = "heredoc";
//	tools->cmd->infile[1][2] = NULL;
//	tools->cmd->infile[2][0] = "txt";
	tools->cmd->infile[2][1] = NULL;
	tools->cmd->infile[3][0] = "LA";
	tools->cmd->infile[3][1] = "hereddoc";
	tools->cmd->infile[3][2] = NULL;
*/	
	tools->cmd->fd_in = 0;
	tools->cmd->fd_out = 1;
	tools->cmd->prev = NULL; 

	tools->cmd->next = NULL;
	tools->t_cmd_size = 1;

/*
	t_cmd *comm1;
	comm1 = malloc(sizeof(t_cmd));
	comm1->arg = ft_split(" ls ", ' ');
	tools->cmd->next = comm1;
	tools->cmd->next->infile = NULL;
	tools->cmd->next->infile = malloc(sizeof(char *) * 2);
	tools->cmd->next->infile[0] = malloc(sizeof(char *) * 3);
	tools->cmd->next->infile[0][0] = "PAS";
	tools->cmd->next->infile[0][1] = "heredoc";
	tools->cmd->next->infile[0][2] = NULL;
	tools->cmd->next->infile[1] = NULL;
	tools->cmd->next->outfile = NULL;
	tools->cmd->next->outfile = malloc(sizeof(char *) * 3);
	tools->cmd->next->outfile[0] = malloc(sizeof(char *) * 3);
	tools->cmd->next->outfile[1] = malloc(sizeof(char *) * 3);
	tools->cmd->next->outfile[0][0] = "txt";
	tools->cmd->next->outfile[0][1] = NULL;
	tools->cmd->next->outfile[0][2] = NULL;
	tools->cmd->next->outfile[1][0] = "outnew";
	tools->cmd->next->outfile[1][1] = "append";
	tools->cmd->next->outfile[1][2] = NULL;
	tools->cmd->next->outfile[2] = NULL;
	tools->cmd->next->fd_in = 0;
	tools->cmd->next->fd_out = 1;
	tools->cmd->next->prev = tools->cmd; 
	comm1->next = NULL;
	tools->t_cmd_size = 2;

	t_cmd *comm2;
	comm2 = malloc(sizeof(t_cmd));
	comm2->arg = ft_split(" cat  ", ' ');
	comm1->next = comm2;
	tools->cmd->next->next->infile = NULL;
	tools->cmd->next->next->outfile = NULL;
	tools->cmd->next->next->fd_in = 0;
	tools->cmd->next->next->fd_out = 1;
	tools->cmd->next->next->prev = tools->cmd->next; 

	tools->cmd->next->next->next = NULL;
	tools->t_cmd_size = 3;


	t_cmd 	*tmp;
	tmp = tools->cmd;
	tools->cmd = tools->cmd->next;
	tools->cmd->next = tmp;
	tmp->prev = tools->cmd;
	tmp->next = comm2;
	tools->cmd->prev = NULL;

//	tools->cmd->next = NULL;
	
	print_cdm_list(tools->cmd);
*/
}


