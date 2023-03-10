/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:34:40 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/10 15:16:16 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	read_map(t_map *map, t_list **info_list)
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
		len = ft_strlen(map->map[i]);
		if (len > map->size.x)
			map->size.x = len;
	}
	map->size.y = i;
}

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
	read_map(&cub->map, &info_list);
	while (*cub->map.map)
		printf("%s\n", *(cub->map.map++));
}
