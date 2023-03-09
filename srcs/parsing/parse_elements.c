/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:23:07 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/09 22:28:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_content(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (ft_strchr("10NSWE ", *str++) == NULL)
			return (0);
	}
	return (1);
}

static int	check_rgba_format(char *rgba_str)
{
	while (*rgba_str != '\0')
	{
		if (ft_isdigit(*rgba_str) == 0 && *rgba_str != ',')
			return (0);
		rgba_str++;
	}
	return (1);
}

static void	store_color(t_cub *cub, unsigned char color[4], char *rgb_str)
{
	int		i;
	int		value;
	char	**rgb_value;

	if (check_rgba_format(rgb_str) == 0)
		exit_cub(cub, INVALID_RGB_FORMAT);
	rgb_value = ft_split(rgb_str, ',');
	if (ft_strarrsize(rgb_value) != 3)
	{
		ft_freestrarr(rgb_value);
		exit_cub(cub, MISSING_RGB_VALUE);
	}
	i = -1;
	while (rgb_value[++i] != NULL)
	{
		value = ft_atoi(rgb_value[i]);
		if (value < 0 || value > 255)
		{
			ft_freestrarr(rgb_value);
			exit_cub(cub, RGB_OUT_OF_RANGE);
		}
		color[i] = (unsigned char)value;
	}
	ft_freestrarr(rgb_value);
}

/**
 * mlx_xpm_file_to_image will return NULL if the initialization failed
*/
void	set_element(t_cub *cub, char **element_set)
{
	if (ft_strcmp(element_set[0], "NO") == 0)
		xpm_to_image(cub, &cub->textures.no_tex, element_set[1]);
	else if (ft_strcmp(element_set[0], "SO") == 0)
		xpm_to_image(cub, &cub->textures.so_tex, element_set[1]);
	else if (ft_strcmp(element_set[0], "WE") == 0)
		xpm_to_image(cub, &cub->textures.we_tex, element_set[1]);
	else if (ft_strcmp(element_set[0], "EA") == 0)
		xpm_to_image(cub, &cub->textures.ea_tex, element_set[1]);
	else if (ft_strcmp(element_set[0], "C") == 0)
	{
		store_color(cub, cub->textures.ceil, element_set[1]);
		cub->textures.info.ceil_set = 1;
	}
	else if (ft_strcmp(element_set[0], "F") == 0)
	{
		store_color(cub, cub->textures.floor, element_set[1]);
		cub->textures.info.floor_set = 1;
	}
	else
		exit_cub(cub, UNKNOWN_ELEMENT);
}

/**
 * Current rules for elements
 * 1. Can accept duplicate identifier for element (?)
 * 2. Format for element: [Identifier] [Path / Value]
 * 3. For RGB, the format should strictly be: R,G,B
 * 4. For RGB, the value for each should range from 0 to 255
 * 5. While parsing elements, if there's an unknown identifier, program should
 * 	  throw "Unknown element" error.
 * 
 * The process of parsing elements will stop when encounter map's content.
*/
void	parse_elements(t_cub *cub, t_list **info_list)
{
	size_t	size;
	t_list	*info;
	char	**element_set;

	info = *info_list;
	while (info != NULL && is_map_content(info->content) == 0)
	{
		element_set = ft_split_ws((char *)info->content);
		size = ft_strarrsize(element_set);
		if (size == 0)
		{
			info = info->next;
			ft_freestrarr(element_set);
			continue ;
		}
		else if (size != 2)
		{
			ft_freestrarr(element_set);
			exit_cub(cub, INVALID_ELEMENT_FORMAT);
		}
		set_element(cub, element_set);
		ft_freestrarr(element_set);
		info = info->next;
	}
	*info_list = info;
}
