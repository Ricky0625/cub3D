/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:21:01 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/11 12:53:13 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* ====== MACROS ====== */
# define NO_MAP "Please provide a map name!"
# define TOO_MANY_MAP "Too many map!"
# define FILE_NOT_FOUND "Map file not found!"
# define INVALID_FILE_EXT "File extension not supported!"
# define EMPTY_FILE "Empty map file!"
# define UNKNOWN_ELEMENT "Unknown identifier for element!"
# define INVALID_ELEMENT_FORMAT "Invalid element format!"
# define INVALID_RGB_FORMAT "Invalid RGB value format"
# define MISSING_RGB_VALUE "RGB value missing"
# define MISSING_ELEMENT "Missing element definition!"
# define RGB_OUT_OF_RANGE "RGB value out of range"
# define MAP_CONTENT_NOT_LAST "Map content is not the last element"
# define NOT_SURROUNDED_BY_WALL "Map is not surrounded by wall"
# define TOO_MANY_PLAYERS "More than one player exists in the map"
# define NO_PLAYER "No player on the map"

#endif