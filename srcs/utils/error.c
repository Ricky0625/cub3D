/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:28:34 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/07 18:43:39 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	show_error(t_cub *cub, t_error err)
{
	(void)cub;
	if (err == NO_MAP)
		ft_printf("Please provide a map name!\n");
	else if (err == TOO_MUCH_MAP)
		ft_printf("Too much map! Please provide one only!\n");
	return (0);
}
