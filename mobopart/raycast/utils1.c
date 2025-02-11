
#include "../include/cub3d.h"

int get_sign(float value)
{
    if (value < 0)
        return (-1);
    return (1);
}

int ft_destroy_exit(t_data *data)
{
    int i;


    // Освобождение изображений (textures)
    i = -1;
    while (++i < 4)
    {
        if (data->texture[i].img)
        {
            mlx_destroy_image(data->mlx, data->texture[i].img);
            data->texture[i].img = NULL;  // Не забываем обнулять указатели после освобождения
        }
    }
        // Проверка на NULL для окна перед очисткой
        if (data->win)
        {
            mlx_clear_window(data->mlx, data->win);
            mlx_destroy_window(data->mlx, data->win);
        }
        
    
    // Освобождение самого mlx, если он был инициализирован
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;  // Обнуляем указатель на mlx после освобождения
    }

    exit(0);  // Завершаем программу
}

