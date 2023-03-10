/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:40:10 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/10 15:05:10 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_texture *texture)
{
	texture->no_tex.ref = NULL;
	texture->so_tex.ref = NULL;
	texture->we_tex.ref = NULL;
	texture->ea_tex.ref = NULL;
	texture->ceil_set = 0;
	texture->floor_set = 0;
}
