/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_manual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:48:07 by wxuerui           #+#    #+#             */
/*   Updated: 2023/07/03 18:17:51 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_manual_string(t_cub *cub, t_vector pos, char *string)
{
	mlx_string_put(cub->mlx, cub->win,
		pos.x, pos.y, MANUAL_TEXT_COLOR, string);
}

static void	put_coords_values(t_cub *cub, t_vector pos,
	char output[MANUAL_MAX_LINE_SIZE], t_manual_args args)
{
	char	*temp_output;
	char	*itoa_temp;

	temp_output = output;
	ft_strcpy(temp_output, args.prefix);
	temp_output += ft_strlen(args.prefix);
	itoa_temp = ft_itoa(args.arg.coords.x);
	ft_strcpy(temp_output, itoa_temp);
	temp_output += ft_strlen(itoa_temp);
	free(itoa_temp);
	ft_strcpy(temp_output, ", ");
	temp_output += 2;
	itoa_temp = ft_itoa(args.arg.coords.y);
	ft_strcpy(temp_output, itoa_temp);
	temp_output += ft_strlen(itoa_temp);
	free(itoa_temp);
	if (args.suffix)
		ft_strcpy(temp_output, args.suffix);
	put_manual_string(cub, pos, output);
}

void	put_single_value(t_cub *cub, t_vector pos,
	char output[MANUAL_MAX_LINE_SIZE], t_manual_args args)
{
	char	*temp_output;
	char	*temp;

	temp_output = output;
	ft_strcpy(temp_output, args.prefix);
	temp_output += ft_strlen(args.prefix);
	if (args.arg_type == VALUE)
	{
		temp = ft_itoa(args.arg.value);
		ft_strcpy(temp_output, temp);
		temp_output += ft_strlen(temp);
		free(temp);
	}
	else if (args.arg_type == BOOL)
	{
		if (args.arg.value)
			temp = "true";
		else
			temp = "false";
		ft_strcpy(temp_output, temp);
		temp_output += ft_strlen(temp);
	}
	if (args.suffix)
		ft_strcpy(temp_output, args.suffix);
	put_manual_string(cub, pos, output);
}

static void	put_manual2(t_cub *cub, int manual_start_x, char output[MANUAL_MAX_LINE_SIZE])
{
	t_manual_variable_arg	var_arg;

	var_arg.value = cub->proj_attr.fov;
	put_single_value(cub, (t_vector){manual_start_x + 20, 160}, output,
		(t_manual_args){"\tFOV: ", var_arg, "", VALUE});
	var_arg.value = cub->render_opt.minimap;
	put_single_value(cub, (t_vector){manual_start_x + 20, 180}, output,
		(t_manual_args){"\tMinimap On: ", var_arg, "", BOOL});
	put_manual_string(cub, (t_vector){manual_start_x + 20, 220},
		"\t\t/// Controls \\\\\\");
}

void	put_manual(t_cub *cub)
{
	int						manual_start_x;
	char					output[MANUAL_MAX_LINE_SIZE];
	t_manual_variable_arg	var_arg;

	manual_start_x = WIN_WIDTH - MANUAL_WIDTH;
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->manual.ref, manual_start_x, 0);
	put_manual_string(cub, (t_vector){manual_start_x + 20, 20},
		"\t\t/// Player State \\\\\\");
	var_arg.coords = cub->player.grid_pos;
	put_coords_values(cub, (t_vector){manual_start_x + 20, 40}, output,
		(t_manual_args){"\tGrid Pos: (", var_arg, ")", COORDS});
	var_arg.coords = (t_vector){cub->player.unit_pos.x, cub->player.unit_pos.y};
	put_coords_values(cub, (t_vector){manual_start_x + 20, 60}, output,
		(t_manual_args){"\tUnit Pos: (", var_arg, ")", COORDS});
	var_arg.value = rad_to_deg(cub->player.viewing_angle);
	put_single_value(cub, (t_vector){manual_start_x + 20, 80}, output,
		(t_manual_args){"\tAngle: ", var_arg, " deg", VALUE});
	put_manual_string(cub, (t_vector){manual_start_x + 20, 120},
		"\t\t/// Render Options \\\\\\");
	var_arg.value = cub->render_opt.fisheye;
	put_single_value(cub, (t_vector){manual_start_x + 20, 140}, output,
		(t_manual_args){"\tFisheye: ", var_arg, "", BOOL});
	put_manual2(cub, manual_start_x, output);
}
