/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:23:07 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/24 17:26:32 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check the format of RGB
 * @attention
 * The format should strictly be constructed by digits and ',' only.
 * @return 1 if the format is correct, 0 if not
*/
static int	check_rgb_format(char *rgba_str)
{
	while (*rgba_str != '\0')
	{
		if (ft_isdigit(*rgba_str) == 0 && *rgba_str != ',')
			return (0);
		rgba_str++;
	}
	return (1);
}

/**
 * @brief Convert RGB str and store it as RGB values
 * @details
 * Check if the RGB is the accepted format. Split the str by ',' and
 * convert each value into integer. The value should be in range of
 * 0 and 255.
 * @attention Colors are stored as ARGB
*/
static void	store_color(t_cub *cub, int *color, char *rgb_str)
{
	int				i;
	int				value;
	char			**rgb_value;
	unsigned char	argb[TOTAL_RGBA];

	if (check_rgb_format(rgb_str) == 0)
		exit_cub(cub, INVALID_RGB_FORMAT);
	rgb_value = ft_split(rgb_str, ',');
	if (ft_strarrsize(rgb_value) != 3)
		exit_cub(cub, MISSING_RGB_VALUE);
	argb[0] = 0;
	i = -1;
	while (rgb_value[++i] != NULL)
	{
		value = ft_atoi(rgb_value[i]);
		if (value < 0 || value > 255)
			exit_cub(cub, RGB_OUT_OF_RANGE);
		argb[i + 1] = (unsigned char)value;
	}
	*color = create_argb(argb);
	printf("color: %06x\n", *color);
	ft_freestrarr(rgb_value);
}

/**
 * @brief Set elements (texture and color)
 * 
 * @param cub main struct
 * @param element_set element set
 * 
 * @details
 * 1. Compare the first element of the set with the valid identifiers.
 * 2. If the identifier is matched, store the element.
 * 3. If the identifier is not matched, exit the program. (Unknown identifier)
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
		store_color(cub, &cub->textures.ceil, element_set[1]);
		cub->textures.ceil_set = 1;
	}
	else if (ft_strcmp(element_set[0], "F") == 0)
	{
		store_color(cub, &cub->textures.floor, element_set[1]);
		cub->textures.floor_set = 1;
	}
	else
		exit_cub(cub, UNKNOWN_ELEMENT);
}

/**
 * Rules for elements
 * 1. Duplicate identifiers are allowed. The last one will be used.
 * 2. Format for element: [Identifier] [Path / Value]
 * 3. For RGB, the format should strictly be: R,G,B. No spaces are allowed.
 * 4. For RGB, the value for each should range from 0 to 255
 * 5. While parsing elements, if there's an unknown identifier, program
 *    should throw "Unknown element" error.
*/

/**
 * @brief Parse elements and store them into struct
 * 
 * @param cub Main struct
 * @param info_list map content in the form of a linked list
 * 
 * @details
 * 1. Iterate through the linked list until it reaches the end or map content.
 * 2. Split the content by whitespaces.
 * 3. If the size of the split is 0, it means that the line is empty. Skip it.
 * 4. If the size of the split is not 2, it means that the format is invalid.
 * 5. If the size of the split is 2, set the element.
 * 6. After the parsing, set the pointer to the first node to the node that
 *    makes the parsing stop.
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
			;
		else if (size != 2)
		{
			ft_freestrarr(element_set);
			exit_cub(cub, INVALID_ELEMENT_FORMAT);
		}
		else
			set_element(cub, element_set);
		ft_freestrarr(element_set);
		info = info->next;
	}
	*info_list = info;
}
