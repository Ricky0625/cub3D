/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:40:10 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/09 15:17:19 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_texture *texture)
{
	texture->no_tex.ref = NULL;
	texture->so_tex.ref = NULL;
	texture->we_tex.ref = NULL;
	texture->ea_tex.ref = NULL;
	texture->info.no_tex_set = 0;
	texture->info.so_tex_set = 0;
	texture->info.we_tex_set = 0;
	texture->info.ea_tex_set = 0;
	texture->info.ceil_set = 0;
	texture->info.floor_set = 0;
}
