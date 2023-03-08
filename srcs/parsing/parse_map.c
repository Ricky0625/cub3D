/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:34:40 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/08 14:54:52 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*get_map_info_list(int map_fd)
{
	t_list	*info_list;
	char	*line;

	line = get_next_line(map_fd);
	info_list = ft_lstnew((void *)line);
	line = get_next_line(map_fd);
	while (line != NULL)
	{
		ft_lstadd_back(&info_list, ft_lstnew((void *)line));
		line = get_next_line(map_fd);
	}
	return (info_list);
}

static void	read_map(t_map *map, t_list **info_list)
{
	int	i;
	int	len;

	while (ft_strncmp((char *)(*info_list)->content, "\n", 2) == 0)
		*info_list = (*info_list)->next;
	map->map = (char **)ft_llto2darr(*info_list, llto2darr_func);
	i = -1;
	map->size.x = 0;
	while (map->map[++i] != NULL)
	{
		len = ft_strlen(map->map[i]);
		if (map->map[i][len - 1] == '\n')
		{
			map->map[i][len - 1] = '\0';
			len--;
		}
		if (len > map->size.x)
			map->size.x = len;
	}
	map->size.y = i;
}

static void	get_elements(t_cub *cub, t_list **info_list)
{
	(void)cub;
	(void)info_list;	
}

void	parse_map(t_cub *cub, char *map_name)
{
	int		map_fd;
	t_list	*info_list;

	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		exit(show_error(cub, INVALID_MAP_FILE));
	info_list = get_map_info_list(map_fd);
	cub->map.info_list = info_list;
	get_elements(cub, &info_list);
	read_map(&cub->map, &info_list);
	for (int i = 0; cub->map.map[i] != NULL; i++)
	{
		printf("%s\n", cub->map.map[i]);
	}
}
