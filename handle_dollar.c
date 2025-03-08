/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:56 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/07 15:21:35 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

static char	*append_str(char *dest, const char *src)
{
	size_t	len_dest;
	size_t	len_src;
	char	*new_str;
	size_t	i;
	size_t	j;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	new_str = malloc(len_dest + len_src + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (dest && dest[i])
	{
		new_str[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		new_str[i + j] = src[j];
		j++;
	}
	new_str[i + j] = '\0';
	if (dest)
		free(dest);
	return (new_str);
}

static char	*expand_var(const char *input, int *i)
{
	int		j;
	char	*var_name;
	char	*value;

	if (input[*i + 1] == '?')
	{
		*i = *i + 2;
		return (ft_itoa(g_exit_status));
	}
	if (input[*i + 1] == '$')
	{
		*i = *i + 2;
		return (ft_itoa(getpid()));
	}
	j = *i + 1;
	while (input[j] && ((input[j] >= 'A' && input[j] <= 'Z')
			|| (input[j] >= 'a' && input[j] <= 'z')
			|| (input[j] >= '0' && input[j] <= '9')
			|| (input[j] == '_')))
	{
		j = j + 1;
	}
	var_name = ft_strndup(input + *i + 1, j - *i - 1);
	value = getenv(var_name);
	if (!value)
		value = "";
	free(var_name);
	*i = j;
	return (ft_strdup(value));
}

static void	process_expansion_char(const char *input, int *i, int *state,
		char **result)
{
	char	ch[2];

	if (input[*i] == '\'' && *state == 0)
		*state = 1;
	else if (input[*i] == '\'' && *state == 1)
		*state = 0;
	else if (input[*i] == '"' && *state == 0)
		*state = 2;
	else if (input[*i] == '"' && *state == 2)
		*state = 0;
	else if (input[*i] == '$' && *state != 1)
	{
		char	*temp;
		temp = expand_var(input, i);
		*result = append_str(*result, temp);
		free(temp);
		return;
	}
	else
	{
		ch[0] = input[*i];
		ch[1] = '\0';
		*result = append_str(*result, ch);
	}
	(*i)++;
}

char	*expand_variables(const char *input)
{
	int		i;
	int		state;
	char	*result;

	i = 0;
	state = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[i])
		process_expansion_char(input, &i, &state, &result);
	return (result);
}
