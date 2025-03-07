/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:22:37 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/06 18:42:56 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "libft/libft.h"

typedef struct s_command
{
	char	**args;
	char	*heredoc_delim;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			count;
}	t_pipeline;

typedef struct s_exec_context
{
	t_pipeline	*pipeline;
	char		**env;
	int			cmd_count;
}	t_exec_context;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		shlvl;
	char	*path;
	char	*home_path;
	char	*pwd;
	char	*old_pwd;
	char	**splitted_path;
	char	**env;
	t_env	*env_lines;
	t_env	*export_lines;
	t_list	*history;
}	t_shell;

typedef struct s_prompt
{
	char	*cmd_line;
	char	*echo;
	char	**strs;
	int		nb_args;
}	t_prompt;

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_IN_SINGLE,
	STATE_IN_DOUBLE,
	STATE_ESCAPING
}				t_state;

typedef struct s_tokenize_context
{
	int		i;
	int		ti;
	char	**tokens;
	char	*curr;
	t_state	state;
}	t_tokenize_context;

#endif
