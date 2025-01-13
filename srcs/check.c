/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:50:14 by clouaint          #+#    #+#             */
/*   Updated: 2025/01/13 17:44:11 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_format(char *filename)
{
	int		i;

	i = 0;
	if (!filename)
	{
		ft_printf("Error : No file\n");
		exit(-1);
	}
	while (filename[i] && filename[i - 1] != '.')
		i++;
	if (!ft_strncmp((filename + i), "cub", 3))
		return ;
	ft_printf("Error : File not .cub\n");
	exit(-1);
}
