/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:39:37 by rabougue          #+#    #+#             */
/*   Updated: 2016/09/23 04:44:22 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	get_piece(t_env *env)
{
	char	*line;
	int		i;

	i = 0;
	get_size_piece(env);
	/*env->piece = (char **)malloc(sizeof(char *) * env->size_form_y);*/
	while (i < env->size_form_y)
	{
		get_next_line(STDIN_FILENO, &line);
		ft_memmove(env->piece[i], line, env->size_form_x);
		/*env->piece[i] = ft_strdup(line);*/
		++i;
		free(line);
	}
}

void	get_size_piece(t_env *env)
{
	char	*line;
	char	*len;
	int		i;

	i = 0;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strstr(line, "Piece ") != NULL)
		{
			while (ft_isdigit(line[i]) != 1)
				++i;
			env->size_form_y = ft_atoi(&line[i]);
			len = ft_itoa(env->size_form_y);
			i += ft_strlen(len);
			free(len);
			env->size_form_x = ft_atoi(&line[i]);
			free(line);
			return ;
		}
		free(line);
	}
}

void	get_map(t_env *env)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_isdigit(line[0]) != 0)
		{
			ft_memmove(env->map[i], &line[4], env->size_map_x);
			++i;
		}
		if (i == env->size_map_y)
		{
			free(line);
			break ;
		}
		free(line);
	}
	env->step = 1;
}

void	get_size_map(t_env *env)
{
	char	*line;
	int		i;
	char	*len;

	i = 0;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strstr(line, "Plateau ") != NULL)
		{
			while (ft_isdigit(line[i]) != 1)
				++i;
			env->size_map_y = ft_atoi(&line[i]);
			len = ft_itoa(env->size_map_y);
			i += ft_strlen(len);
			free(len);
			env->size_map_x = ft_atoi(&line[i]);
			free(line);
			return ;
		}
		free(line);
	}
}

void	get_info_header(t_env *env, char **argv)
{
	char	*line;

	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strstr(line, "$$$ exec p1") != NULL)
		{
			if (ft_strstr(line, &argv[0][2]) != NULL)
			{
				env->player = 'O';
				/*env->rabougue = 1;*/
				/*env->ennemi = 2;*/
			}
			else
			{
				env->player = 'X';
				/*env->ennemi = 1;*/
				/*env->rabougue = 2;*/
			}
			free(line);
			return ;
		}
		free(line);
	}
}
