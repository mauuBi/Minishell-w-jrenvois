/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:57:31 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/22 11:33:04 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	**get_path(char **envp)
{
	int		i;
	char	**res;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			res = ft_split(envp[i] + 5, ':');
			return (res);
		}
		i++;
	}
	return (NULL);
}

static t_cmd_res	check_file_status(char *path)
{
	t_cmd_res		result;
	struct stat		statbuf;

	result = (t_cmd_res){0};
	if (access(path, F_OK))
	{
		result.error_code = 127;
		result.error_msg = "No such file or directory";
		return (result);
	}
	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		result.error_code = 126;
		result.error_msg = "Is a directory";
		return (result);
	}
	if (access(path, X_OK))
	{
		result.error_code = 126;
		result.error_msg = "Permission denied";
		return (result);
	}
	result.path = ft_strdup(path);
	return (result);
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

static t_cmd_res	search_in_path(char *cmd, char **path)
{
	t_cmd_res	result;
	char		*full_path;
	int			i;

	result = (t_cmd_res){NULL, 127, "command not found"};
	i = 0;
	while (path[i])
	{
		full_path = build_full_path(path[i], cmd);
		if (!full_path)
			return (result);
		if (!access(full_path, F_OK))
		{
			result = check_file_status(full_path);
			if (!result.error_code)
			{
				free(full_path);
				return (result);
			}
		}
		free(full_path);
		i++;
	}
	return (result);
}

t_cmd_res	find_cmd_in_path(char *cmd, char **path)
{
	t_cmd_res	result;

	result = (t_cmd_res){NULL, 127, "command not found"};
	if (!cmd || !cmd[0])
		return (result);
	if (ft_strchr(cmd, '/'))
		return (check_file_status(cmd));
	if (!path)
		return (check_file_status(cmd));
	return (search_in_path(cmd, path));
}
