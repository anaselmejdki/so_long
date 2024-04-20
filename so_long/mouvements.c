/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:27:41 by ael-mejd          #+#    #+#             */
/*   Updated: 2024/04/20 12:08:03 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_data *data)
{
	free_map(data->map);
	mlx_destroy_window(data->mlx, data->win);
	write(1, "exit by user\n", 13);
	exit(EXIT_SUCCESS);
}

void	change_player_position(t_data *data)
{
	if (data->map[data->p_y + data->dy][data->p_x + data->dx] == '1')
		return ;
	if (data->map[data->p_y + data->dy][data->p_x + data->dx] == 'C')
		data->c_number--;
	if (data->c_number == 0 && data->map[data->p_y + data->dy][data->p_x
		+ data->dx] == 'E')
		exit_game(data);
	else if (data->c_number != 0 && data->map[data->p_y + data->dy][data->p_x
			+ data->dx] == 'E')
		return ;
	data->map[data->p_y][data->p_x] = '0';
	data->map[data->p_y + data->dy][data->p_x + data->dx] = 'P';
	data->p_y = data->p_y + data->dy;
	data->p_x = data->p_x + data->dx;
	ft_putnbr_fd(++data->num_of_moves, 1);
	write(1, "\n", 1);
}

int	handle_keys(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_game(data);
	if (keycode == RIGHT_D || keycode == RIGHT)
	{
		data->dy = 0;
		data->dx = 1;
	}
	if (keycode == LEFT_A || keycode == LEFT)
	{
		data->dy = 0;
		data->dx = -1;
	}
	if (keycode == UP_W || keycode == UP)
	{
		data->dy = 1;
		data->dx = 0;
	}
	if (keycode == DOWN_S || keycode == DOWN)
	{
		data->dy = -1;
		data->dx = 0;
	}
	change_player_position(data);
	draw_map(data);
	return (0);
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			mlx_put_image_to_window(data->mlx, data->win, data->ground, j * 30,
					i * 30);
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall, j
						* 30, i * 30);
			else if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->apple, j
						* 30, i * 30);
			else if (data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->player, j
						* 30, i * 30);
			else if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exit, j
						* 30, i * 30);
			j++;
		}
		i++;
	}
}

void	load_images(t_data *data)
{
	int	width;
	int	height;

	data->ground = mlx_xpm_file_to_image(data->mlx, "./textures/ground.xpm",
			&width, &height);
	if (!data->ground)
		return ;
	data->wall = mlx_xpm_file_to_image(data->mlx, "./textures/wall.xpm", &width,
			&height);
	if (!data->wall)
		return ;
	data->apple = mlx_xpm_file_to_image(data->mlx, "./textures/apple.xpm",
			&width, &height);
	if (!data->apple)
		return ;
	data->player = mlx_xpm_file_to_image(data->mlx, "./textures/left1.xpm",
			&width, &height);
	if (!data->player)
		return ;
	data->exit = mlx_xpm_file_to_image(data->mlx, "./textures/exit_close.xpm",
			&width, &height);
	if (!data->exit)
		return ;
}