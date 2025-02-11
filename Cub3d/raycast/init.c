#include "../include/cub3d.h"

/*void find_player_position(t_data *data)
{
    while (data->temp_i < data->map_height)
    {
        while (data->temp_j < data->map_width)
        {
            if (strchr("NSWE", data->map[data->temp_i][data->temp_j]))
            {
                data->x_pos = data->temp_j;
                data->y_pos = data->temp_i;
                if (data->map[data->temp_i][data->temp_j] == 'E')
                    data->player_angle = 0;
                else if (data->map[data->temp_i][data->temp_j] == 'N')
                    data->player_angle = M_PI / 2;
                else if (data->map[data->temp_i][data->temp_j] == 'W')
                    data->player_angle = M_PI;
                else if (data->map[data->temp_i][data->temp_j] == 'S')
                    data->player_angle = 3 * M_PI / 2;
                return;
            }
            data->temp_j++;
        }
        data->temp_i++;
        data->temp_j = 0;
    }
}*/

void ft_resoures_initialisation(t_data *data)
{
    int i = 0;

    while (++i < 4) 
    {
        /*if (data->path_text[i])
            printf("data->path_text[%d] = %s\n", i, data->path_text[i]);
        else
        {
            printf("Error: path_text[%d] is NULL\n", i);
            ft_destroy_exit(data);
        }*/
       data->path_text[0] = "/mnt/c/Users/sruza/OneDrive/Desktop/проекты/finish/Cub3d/textures/N.xpm";
        data->path_text[1] = "/mnt/c/Users/sruza/OneDrive/Desktop/проекты/finish/Cub3d/textures/S.xpm";
        data->path_text[2] = "/mnt/c/Users/sruza/OneDrive/Desktop/проекты/finish/Cub3d/textures/W.xpm";
        data->path_text[3] = "/mnt/c/Users/sruza/OneDrive/Desktop/проекты/finish/Cub3d/textures/E.xpm";

        data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->path_text[i],
                &data->texture[i].width, &data->texture[i].height);

        if (!data->texture[i].img)
        {
            printf("Error\nCan't read texture file: %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }

        // Новый блок с проверками
        if (data->texture[i].img == NULL) {
            printf("Error: mlx_xpm_file_to_image() returned NULL for %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }

        data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
                &data->texture[i].bits_per_pixel, &data->texture[i].line_length,
                &data->texture[i].endian);

        if (!data->texture[i].addr)
        {
            printf("Error\nFailed to get image data for texture: %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }
    }
}



/*
void ft_resoures_initialisation(t_data *data)
{
    // Проверка путей к файлам текстур
    if (data->path_text[0] == NULL || access(data->path_text[0], F_OK) == -1) {
        printf("Loading texture from path: %s\n", data->path_text[0]);

        printf("Error: Texture file not found at %s\n", data->path_text[0]);
        ft_destroy_exit(data);  //59
    }

    if (data->path_text[1] == NULL || access(data->path_text[1], F_OK) == -1) {
        printf("Error: Texture file not found at %s\n", data->path_text[1]);
        ft_destroy_exit(data);
    }

    if (data->path_text[2] == NULL || access(data->path_text[2], F_OK) == -1) {
        printf("Error: Texture file not found at %s\n", data->path_text[2]);
        ft_destroy_exit(data);
    }

    if (data->path_text[3] == NULL || access(data->path_text[3], F_OK) == -1) {
        printf("Error: Texture file not found at %s\n", data->path_text[3]);
        ft_destroy_exit(data);
    }

    // Загрузка и получение данных текстур
    data->texture[0].img = mlx_xpm_file_to_image(data->mlx, data->path_text[0],
                &data->texture[0].width, &data->texture[0].height);
    if (!data->texture[0].img)
    {
        printf("Error\nCan't read texture file: %s\n", data->path_text[0]);
        ft_destroy_exit(data);
    }
    printf("Texture 0 loaded: %s\n", data->path_text[0]);
    data->texture[0].addr = mlx_get_data_addr(data->texture[0].img,
                &data->texture[0].bits_per_pixel, &data->texture[0].line_length,
                &data->texture[0].endian);
    if (!data->texture[0].addr)
    {
        printf("Error\nFailed to get image data for texture:  %s\n", data->path_text[0]);
        ft_destroy_exit(data);
    }

    data->texture[1].img = mlx_xpm_file_to_image(data->mlx, data->path_text[1],
                &data->texture[1].width, &data->texture[1].height);
    if (!data->texture[1].img)
    {
        printf("Error\nCan't read texture file: %s\n", data->path_text[1]);
        ft_destroy_exit(data);
    }
    printf("Texture 1 loaded: %s\n", data->path_text[1]);
    data->texture[1].addr = mlx_get_data_addr(data->texture[1].img,
                &data->texture[1].bits_per_pixel, &data->texture[1].line_length,
                &data->texture[1].endian);
    if (!data->texture[1].addr)
    {
        printf("Error\nFailed to get image data for texture:  %s\n", data->path_text[1]);
        ft_destroy_exit(data);
    }

    data->texture[2].img = mlx_xpm_file_to_image(data->mlx, data->path_text[2],
                &data->texture[2].width, &data->texture[2].height);
    if (!data->texture[2].img)
    {
        printf("Error\nCan't read texture file: %s\n", data->path_text[2]);
        ft_destroy_exit(data);
    }
    printf("Texture 2 loaded: %s\n", data->path_text[2]);
    data->texture[2].addr = mlx_get_data_addr(data->texture[2].img,
                &data->texture[2].bits_per_pixel, &data->texture[2].line_length,
                &data->texture[2].endian);
    if (!data->texture[2].addr)
    {
        printf("Error\nFailed to get image data for texture:  %s\n", data->path_text[2]);
        ft_destroy_exit(data);
    }

    data->texture[3].img = mlx_xpm_file_to_image(data->mlx, data->path_text[3],
                &data->texture[3].width, &data->texture[3].height);
    if (!data->texture[3].img)
    {
        printf("Error\nCan't read texture file: %s\n", data->path_text[3]);
        ft_destroy_exit(data);
    }
    printf("Texture 3 loaded: %s\n", data->path_text[3]);
    data->texture[3].addr = mlx_get_data_addr(data->texture[3].img,
                &data->texture[3].bits_per_pixel, &data->texture[3].line_length,
                &data->texture[3].endian);
    if (!data->texture[3].addr)
    {
        printf("Error\nFailed to get image data for texture:  %s\n", data->path_text[3]);
        ft_destroy_exit(data);
    }
}*/

/*
void ft_param_initialisation(t_data *data)
{
    data->map_height = 10;
    data->map_width = 12;
    data->x_pos = 0.0;
    data->y_pos = 0.0;
    data->temp_j = 0;
    data->temp_i = 0;
    data->color_ceiling = 0x87CEEB;
    data->color_floor = 0x2E8B57;
    data->path_text[0] = "./textures/N.xpm";
    data->path_text[1] = "./textures/E.xpm";
    data->path_text[2] = "./textures/S.xpm";
    data->path_text[3] = "./textures/W.xpm";
    data->mlx = mlx_init();
    if (!data->mlx)
    {
         printf("Error: mlx_init() returned NULL\n");
         exit(1);
    }
    data->win = mlx_new_window(data->mlx, WINDOW_W, WINDOW_H, "data");
    if (!data->win)
    {
        printf("Error: data.win == NULL\n");
        exit(1);
    }
}

int main() {
    t_data data;
    char *map[] = {
        "111111111111",
        "100000000101",
        "100000010001",
        "1000000000S1",
        "100000010001",
        "100000000001",
        "100000000001",
        "100000000001",
        "100000010001",
        "111111111111",
    };
    data.map = map;
    ft_param_initialisation(&data);
    ft_resoures_initialisation(&data);
    find_player_position(&data);
    ft_draw(&data);
    mlx_key_hook(data.win, ft_key, (void *)&data);
   // mlx_hook(data.win, 2, 1, ft_key, (void *)&data);
    mlx_hook(data.win, 17, 0, ft_destroy_exit, (void *)&data); 
   // mlx_hook(data.win, 17, 0, mlx_loop_end, (void *)&data); 
    mlx_loop(data.mlx);
    ft_destroy_exit(&data);
    return (0);
}*/
