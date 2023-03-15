/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:56:01 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/14 17:04:56 by wricky-t         ###   ########.fr       */
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

void	new_rect(t_cub *cub, t_img *img, t_vector size, int color)
{
	int	x;
	int	y;
	int	pixel;

	new_image(cub, img, size);
	if (img->ref == NULL || img->data == NULL)
		return ;
	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
		{
			pixel = (y * img->line_size) + (x * 4);
			ft_memcpy(&img->data[pixel], &color, sizeof(int));
		}
	}
}

void	copy_image(t_img *src, t_img *dst, t_vector d_pos)
{
	int	x;
	int	y;
	int	src_pixel;
	int	dst_pixel;

	if (src->ref == NULL || dst->ref == NULL)
		return ;
	y = -1;
	while (++y < src->size.y)
	{
		x = -1;
		while (++x < src->size.x)
		{
			src_pixel = (y * src->line_size) + (x * 4);
			dst_pixel = ((d_pos.y + y) * dst->line_size) + ((d_pos.x + x) * 4);
			ft_memcpy(&dst->data[dst_pixel], &src->data[src_pixel],
				sizeof(int));
		}
	}
}
