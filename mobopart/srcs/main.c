/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:23:50 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 19:46:07 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void init_data(t_data *data)
{
    //int i;

    // Инициализация всех указателей в NULL
    data->file = NULL;
    data->c_color = NULL;
    data->f_color = NULL;
    data->path_text[0] = NULL;
    data->path_text[1] = NULL;
    data->path_text[2] = NULL;
    data->path_text[3] = NULL;
    data->map = NULL;
    data->new_map = NULL;

    // Инициализация позиций игрока и карты
    data->x_pos = -1;
    data->y_pos = -1;
    data->map_length = 0;
    data->map_start = -1;
    data->end_map = -1;
    data->player_angle = 0.0;
    data->player_x = 0.0;
    data->player_y = 0.0;
    // Инициализация массива текстур
   /* for (i = 0; i < 4; i++) {
        data->texture[i].img = NULL;
        data->texture[i].addr = NULL;
        data->texture[i].width = 0;
        data->texture[i].height = 0;
        data->texture[i].bits_per_pixel = 0;
        data->texture[i].line_length = 0;
        data->texture[i].endian = 0;
    }*/

    // Инициализация переменных отображения
    data->map_width = 0;
   /*data->mlx = NULL;
    data->win = NULL;
    data->img.img = NULL;
    data->img.addr = NULL;*/
    data->textur_index = 0;
    data->textur_shift = 0.0;
    data->view = 0.0;
}


#include <stdio.h>

void print_data(t_data *data)
{
    printf("=== Информация о текстурах ===\n");
    printf("Север: %s\n", data->path_text[0] ? data->path_text[0] : "Не задано");
    printf("Юг: %s\n", data->path_text[2] ? data->path_text[2] : "Не задано");
    printf("Запад: %s\n", data->path_text[3] ? data->path_text[3] : "Не задано");
    printf("Восток: %s\n", data->path_text[1] ? data->path_text[1] : "Не задано");

    printf("\n=== Цвета стен ===\n");
    if (data->f_color)
        printf("Цвет пола: %d\n", *data->f_color);
    else
        printf("Цвет пола: Не задано\n");

    if (data->c_color)
        printf("Цвет потолка: %d\n", *data->c_color);
    else
        printf("Цвет потолка: Не задано\n");

    printf("\n=== Позиция игрока ===\n");
    printf("X: %d, Y: %d\n", data->x_pos, data->y_pos);
}

void ft_mls(t_data *data)
{
    data->player_x = data->x_pos;
    data->player_y = data->y_pos;
	data->mlx = mlx_init(); //стр 61
	if (!data->mlx) {
		printf("Error: mlx_init() returned NULL\n");
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, WINDOW_W, WINDOW_H, "data");
	if (!data->win) {
		printf("Error: mlx_new_window() returned NULL\n");
		exit(1);
	}
	
	printf("data->mlx: %p\n", data->mlx);
	ft_resoures_initialisation(data);
	printf("1\n");
	if (data->mlx == NULL || data->win == NULL)
	{
		printf("Error: MLX not initialized properly!\n");
	}

	ft_draw(data);
	printf("2\n");
    mlx_key_hook(data->win, ft_key, (void *)&data);
	printf("3\n");
	mlx_hook(data->win, 17, 0, ft_destroy_exit, (void *)&data);
	printf("5\n");
	mlx_loop(data->mlx);//102 строка
	printf("6\n"); // не печатает
    ft_destroy_exit(data);
}

void	parsing_cub(char *argv)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		err(data, MALLOC);
	memset(data, 0, sizeof(t_data));
	init_data(data);
	if (!is_valid_data_extension(argv))
		err(data, EXTENSION);
	copy_cub_file(argv, data);
	where_is_the_map(data, data->file, &data->map_length);
	save_map(data, data->file, &data->map, &data->map_length);
	printf("map_length - %d\n", data->map_length);
	extract_textures(data);
	extract_valid_colors(data);
	if (are_colors_and_textures_before_map(data, 0) == false)
		err(data, TXT_AFTER_MAP);
	//file_is_clean(data);
	parsing_map(data);
	print_data(data);
	//free_all(data);
	//ft_mls(data);//109 строка
    ft_draw(data);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	parsing_cub(argv[1]);//116 стр
	return (0);
}
