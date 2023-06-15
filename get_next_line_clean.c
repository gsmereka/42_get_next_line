/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_clean.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 02:24:40 by gsmereka          #+#    #+#             */
/*   Updated: 2023/06/15 16:40:33 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *next_s);
static char	*ft_actual_s(char *str);
static char	*ft_define_next_s(char *str);

char	*get_next_line_clean(int fd, int clean)
{
	char		*actual_s;
	static char	*next_s[1024];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	if (clean == 1)
	{
		free(next_s[fd]);
		next_s[fd] = NULL;
		return (NULL);
	}
	next_s[fd] = ft_read(fd, next_s[fd]);
	if (!next_s[fd])
		return (NULL);
	actual_s = ft_actual_s(next_s[fd]);
	next_s[fd] = ft_define_next_s(next_s[fd]);
	return (actual_s);
}

static char	*ft_read(int fd, char *next_s)
{
	char	*temp_s;
	int		stop;

	temp_s = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_s)
		return (NULL);
	stop = 1;
	while (stop != 0 && !ft_strchr(next_s, '\n'))
	{
		stop = read(fd, temp_s, BUFFER_SIZE);
		if (stop == -1)
		{
			free(temp_s);
			return (NULL);
		}
		temp_s[stop] = '\0';
		ft_addstr(&next_s, temp_s);
	}
	free(temp_s);
	return (next_s);
}

static char	*ft_actual_s(char *s)
{
	char	*new_s;
	int		i;
	int		limit;

	if (s[0] == '\0')
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		i++;
	new_s = malloc((i + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	limit = 0;
	while (limit < i)
	{
		new_s[limit] = s[limit];
		limit++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static char	*ft_define_next_s(char *s)
{
	char	*new_s;
	int		n_pos;
	int		new_end;

	n_pos = 0;
	while (s[n_pos] != '\0' && s[n_pos] != '\n')
		n_pos++;
	if (s[n_pos] == '\0')
	{
		free(s);
		return (NULL);
	}
	n_pos++;
	new_s = (char *)malloc((1 + (ft_strlen(s) - n_pos)) * sizeof(char));
	if (new_s == NULL)
	{
		free(s);
		return (NULL);
	}
	new_end = 0;
	while (s[n_pos] != '\0')
		new_s[new_end++] = s[n_pos++];
	new_s[new_end] = '\0';
	free(s);
	return (new_s);
}
