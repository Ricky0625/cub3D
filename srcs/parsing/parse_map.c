/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:34:40 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/11 12:37:58 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if all 0s and player are surrounded by other 1 or 0
 * and only one player exists
 * 
 * @param cub 
 * @param map
 * @return int 1 for true, 0 for false
 */
static void	check_map(t_cub *cub, t_map *map)
{
	int	num_player;
	int	i;
	int	j;

	num_player = 0;
	i = -1;
	while (map->map[++i] != NULL)
	{
		j = -1;
		while (map->map[i][++j] != '\0')
		{
			if (ft_strchr("NSWE", map->map[i][j]) != NULL)
				num_player++;
			if (num_player > 1)
				exit_cub(cub, TOO_MANY_PLAYERS);	
			if (map->map[i][j] == '0' || ft_strchr("NSWE", map->map[i][j]) != NULL)
			{
				if (check_surrounded(map, i, j) == 0)
					exit_cub(cub, NOT_SURROUNDED_BY_WALL);
			}
		}
	}
	if (num_player == 0)
		exit_cub(cub, NO_PLAYER);
}

/**
 * @brief Check file extension and open map file
 * @return Fd of map
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
 * @brief Read the map content into the 2darr in the map struct
 * 
 * @param cub 
 * @param map 
 * @param info_list 
 */
void	read_map(t_cub *cub, t_map *map, t_list **info_list)
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
 * @brief First get the mapfile content line by line into a linked list,
 * Then parse and load the elements (textures and colors),
 * Then parse the rest of the lines (which are the map contents),
 * Lastly check errors for this whole map
 * 
 * @param cub 
 * @param map_name 
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
	read_map(cub, &cub->map, &info_list);
	// while (*cub->map.map)
	// 	printf("%s\n", *(cub->map.map++));
	check_map(cub, &cub->map);
}
