/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:28:34 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/15 15:17:37 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Free everything and exit
*/
void	exit_cub(t_cub *cub, char *err)
{
	int	exit_status;

	(void)cub;
	exit_status = EXIT_SUCCESS;
	if (err != NULL)
	{
		ft_printf("[ERROR]: %s\n", err);
		exit_status = EXIT_FAILURE;
	}
	exit(exit_status);
}
