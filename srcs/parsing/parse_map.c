/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:34:40 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/20 11:56:58 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check the validity of the map
 * 
 * @param cub main struct
 * 
 * @details
 * 1. Iterate through the map using map_iterator
 * 2. If the player is not set, exit with error
 */
static void	check_map(t_cub *cub)
{
	map_iterator(cub, validate_map, COLUMN);
	if (cub->player.dir == UNDEFINED)
		exit_cub(cub, NO_PLAYER);
}

/**
 * @brief Check file extension and open map file
 * 
 * @param cub      main struct
 * @param map_name map file name
 * 
 * @details
 * 1. Check if the file extension is .cub (as long as it ends with .cub)
 * 2. Open the map file
 * 3. If the file does not exist, exit with error
 * 
 * @return Fd of the map file
*/
static int	open_file(t_cub *cub, char *map_name)
{
	int		map_fd;
	char	*ext;

	ext = ft_strrchr(map_name, '.');
	if (ext == NULL || ft_strcmp(FILE_EXT, ext) != 0)
		exit_cub(cub, INVALID_FILE_EXT);
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		exit_cub(cub, FILE_NOT_FOUND);
	return (map_fd);
}

/**
 * @brief Get map info list
 * 
 * @param lst    The list to store map info
 * @param map_fd The fd of map file
 * 
 * @details
 * 1. Read each line of the map file
 * 2. Remove the '\n' at the end of each line
 * 3. Store each line as a node of the list
*/
static void	get_map_info_list(t_list **lst, int map_fd)
{
	t_list	*info_list;
	char	*line;

	while (1)
	{
		line = get_next_line(map_fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		info_list = ft_lstnew((void *)line);
		ft_lstadd_back(lst, info_list);
	}
}

/**
 * @brief Read the map content into a 2d array and get its metadata
 * 
 * @param cub		main struct
 * @param map 		map file name
 * @param info_list map info list (pointer to the first node)
 * 
 * @details
 * 1. Skip the empty lines at the beginning of the map file
 * 2. Read the map content into the 2darr in the map struct
 * 3. Check if the current line we are examine belongs to the map content
 * 4. Update the width and height of the map
 */
static void	read_map(t_cub *cub, t_map *map, t_list **info_list)
{
	int	i;
	int	len;

	while (*info_list != NULL && ((char *)((*info_list)->content))[0] == '\0')
		*info_list = (*info_list)->next;
	map->map = (char **)ft_llto2darr(*info_list, llto2darr_func);
	i = -1;
	map->size.x = 0;
	while (map->map[++i] != NULL)
	{
		if (is_map_content(map->map[i]) == 0)
			exit_cub(cub, MAP_CONTENT_NOT_LAST);
		len = ft_strlen(map->map[i]);
		if (len > map->size.x)
			map->size.x = len;
	}
	map->size.y = i;
}

/**
 * @brief Map parser
 * 
 * @param cub      main struct
 * @param map_name map file name
 * 
 * @details
 * 1. Check file extension and open map file
 * 2. Get map info list
 * 3. Parse and load the elements (textures and colors)
 * 4. Parse the rest of the lines (which are the map contents)
 * 5. Check the validity of the map
 */
void	parse_map(t_cub *cub, char *map_name)
{
	int		map_fd;
	t_list	*info_list;

	map_fd = open_file(cub, map_name);
	get_map_info_list(&cub->map.info_list, map_fd);
	info_list = cub->map.info_list;
	if (info_list == NULL)
		exit_cub(cub, EMPTY_FILE);
	parse_elements(cub, &info_list);
	if (check_elements_all_set(&cub->textures) == 0)
		exit_cub(cub, MISSING_ELEMENT);
	read_map(cub, &cub->map, &info_list);
	check_map(cub);

	printf("doors: %d\n", ft_lstsize(cub->doors));
}
