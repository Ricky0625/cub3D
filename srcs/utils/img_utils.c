/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:56:01 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/09 12:54:11 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Create new empty image.
*/
void	new_image(t_cub *cub, t_img *img, t_vector size)
{
	img->ref = mlx_new_image(cub->mlx, size.x, size.y);
	img->size = size;
	img->data = mlx_get_data_addr(img->ref, &img->bpp, &img->line_size,
			&img->endian);
}

/**
 * @brief Convert xpm to image.
*/
void	xpm_to_image(t_cub *cub, t_img *img, char *xpm)
{
	img->ref = mlx_xpm_file_to_image(cub->mlx, xpm,
			&img->size.x, &img->size.y);
	img->data = mlx_get_data_addr(img->ref, &img->bpp, &img->line_size,
			&img->endian);
}
