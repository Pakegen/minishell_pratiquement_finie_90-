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

int	g_exit_status;

static char	*append_str(char *dest, const char *src)
{
	size_t	len_dest = ft_strlen(dest);
	size_t	len_src = ft_strlen(src);
	char	*new_str = malloc(len_dest + len_src + 1);
	if (!new_str)
		return (NULL);
	size_t	i = 0, j = 0;
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
	int	j;
	char 	*var_name;
	char 	*value;

	j = *i + 1;
	if (input[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(g_exit_status));
	}
	while (input[j] && ((input[j] >= 'A' && input[j] <= 'Z')
		|| (input[j] >= 'a' && input[j] <= 'z')
		|| (input[j] >= '0' && input[j] <= '9')
		|| input[j] == '_'))
	{
		j++;
	}
	var_name = ft_strndup(input + *i + 1, j - *i - 1);
	value = getenv(var_name);
	if (!value)
		value = "";
	free(var_name);
	*i = j;
	return (ft_strdup(value));
}

char	*expand_variables(const char *input)
{
	int		i = 0;
	int		state = 0; /* 0 = non cité, 1 = cité en simple, 2 = cité en double */
	char	*result = ft_strdup("");
	char	ch[2];

	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && state == 0)
			state = 1;
		else if (input[i] == '\'' && state == 1)
			state = 0;
		else if (input[i] == '"' && state == 0)
			state = 2;
		else if (input[i] == '"' && state == 2)
			state = 0;
		else if (input[i] == '$' && state != 1)
		{
			char *temp = expand_var(input, &i);
			result = append_str(result, temp);
			free(temp);
			continue;
		}
		else
		{
			ch[0] = input[i];
			ch[1] = '\0';
			result = append_str(result, ch);
		}
		i++;
	}
	return (result);
}
