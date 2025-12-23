/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:41:37 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 23:02:54 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_vars(char ***env)
{
	char	*current_pwd;
	char	*old_pwd;
	int		pwd_index;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	pwd_index = env_var_index("PWD", env);
	if (pwd_index != -1)
	{
		old_pwd = ft_strchr((*env)[pwd_index], '=');
		if (old_pwd)
			set_env_var("OLDPWD", old_pwd + 1, env);
	}
	set_env_var("PWD", current_pwd, env);
	free(current_pwd);
	return (0);
}

static int	ret_error(char *dir_name)
{
	char	*error;
	size_t	total_size;
	char	*res_err;

	error = strerror(errno);
	total_size = 19 + ft_strlen(error) + ft_strlen(dir_name);
	res_err = ft_calloc(1, total_size);
	if (!res_err)
		return (ft_putstr_fd("minishell: malloc error\n", 2), -1);
	ft_strlcat(res_err, "minishell: cd: ", total_size);
	ft_strlcat(res_err, dir_name, total_size);
	ft_strlcat(res_err, ": ", total_size);
	ft_strlcat(res_err, error, total_size);
	ft_strlcat(res_err, "\n", total_size);
	ft_putstr_fd(res_err, 2);
	free(res_err);
	return (1);
}

static void	print_env_var(char *key, char ***env)
{
	int		var_index;
	char	*equal_pos;

	var_index = env_var_index(key, env);
	if (var_index == -1)
		return ;
	equal_pos = ft_strchr((*env)[var_index], '=');
	if (!equal_pos)
		return ;
	ft_putstr_fd(equal_pos + 1, 1);
	ft_putstr_fd("\n", 1);
}

static int	goto_env(char *key, char ***env)
{
	int		var_index;
	char	*equal_pos;

	var_index = env_var_index(key, env);
	if (var_index == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd(" not set\n", 2);
		return (1);
	}
	equal_pos = ft_strchr((*env)[var_index], '=');
	if (!equal_pos)
		return (1);
	if (chdir(equal_pos + 1) == -1)
		return (ret_error(equal_pos + 1));
	return (update_pwd_vars(env));
}

int	ft_cd(char **args, char ***env)
{
	if (!args || !args[0])
		return (-1);
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (args[1])
	{
		if (!ft_strncmp(args[1], "-", INT_MAX))
			return (print_env_var("OLDPWD", env),
				goto_env("OLDPWD", env));
		else
		{
			if (chdir(args[1]) == -1)
				return (ret_error(args[1]));
			return (update_pwd_vars(env));
		}
	}
	else
	{
		return (goto_env("HOME", env));
	}
	return (1);
}
