/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:56:01 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/03 14:56:01 by wxuerui          ###   ########.fr       */
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
	if (img->ref == NULL)
		return ;
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
	if (img->ref == NULL)
		return ;
	img->data = mlx_get_data_addr(img->ref, &img->bpp, &img->line_size,
			&img->endian);
}

void	put_color_to_image(t_img *img, int color, int size)
{
	int	i;

	i = -1;
	while (++i < size * img->bpp / 8)
	{
		img->data[i] = color;
		img->data[++i] = color >> 8;
		img->data[++i] = color >> 16;
		img->data[++i] = color >> 24;
	}
}
