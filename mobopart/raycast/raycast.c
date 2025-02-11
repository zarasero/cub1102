#include "../include/cub3d.h"

void initialize_ray(t_data *data, Ray *ray, float angle)
{
    ray->direction_x = cos(angle);
    ray->direction_y = -sin(angle);
    ray->step_x = get_sign(ray->direction_x);
    ray->step_y = get_sign(ray->direction_y);
    ray->next_vertical_x = floor(data->player_x) + (ray->step_x > 0);
    ray->next_horizontal_y = floor(data->player_y) + (ray->step_y > 0);
}

static float save_texture_info(t_data *data, float distance, int texture_index, float texture_x)
{
    data->textur_index= texture_index;
    data->textur_shift = texture_x;
    return (distance);
}

void calculate_next_intersection(t_data *data, Ray *ray)
{
    printf("70\n");
    if (ray->step_x != 0)
    {
        printf("71\n");
        ray->next_vertical_y = data->player_y + ray->direction_y / ray->direction_x * (ray->next_vertical_x - data->player_x);
        ray->vertical_distance = sqrt(pow(data->player_x - ray->next_vertical_x, 2.0) + pow(data->player_y - ray->next_vertical_y, 2.0));
        ray->texture_x = ray->next_vertical_y - (int) ray->next_vertical_y;
        if (ray->step_x > 0)
            ray->texture_x = 1 - ray->texture_x;
    } 
    else
    {
        printf("72\n");
        ray->vertical_distance = INFINITY;
    }
    if (ray->step_y != 0)
    {
        printf("73\n");
        ray->next_horizontal_x = data->player_x + ray->direction_x / ray->direction_y * (ray->next_horizontal_y - data->player_y);
        ray->horizontal_distance = sqrt(pow(data->player_x - ray->next_horizontal_x, 2.0) + pow(data->player_y - ray->next_horizontal_y, 2.0));
        ray->texture_y = ray->next_horizontal_x - (int) ray->next_horizontal_x;
        if (ray->step_y < 0) ray->texture_y = 1 - ray->texture_y;
    }
    else
    {
        printf("74\n");
        ray->horizontal_distance = INFINITY;
    }
}

float handle_check(t_data *data, Ray *ray, int flag)
{
    if(flag == 1)
    {
        ray->map_x = (int)ray->next_vertical_x;
        ray->map_y = (int)ray->next_vertical_y;
    }
    else
    {
        ray->map_y = (int)ray->next_horizontal_y;
        ray->map_x = (int)ray->next_horizontal_x;
    }
    if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0 || ray->map_y >= data->map_length + 2)
    {
        printf("Error: out of bounds array access");
        return (-1);
    }
    return (0);
}

float handle_vertical_intersection(t_data *data, Ray *ray)
{
    int texture_index;
    int map_x_offset;

    printf("Проверка карты:\n");
    for (int i = 0; data->new_map[i]; i++)
         printf("%s\n", data->new_map[i]);


    if (handle_check(data, ray, 1) == -1)
        return (-1);
    if (ray->step_x > 0)
        map_x_offset = 0;
    else
        map_x_offset = -1;
    if (data->new_map[ray->map_y][ray->map_x + map_x_offset] == '1')
    {
        if (ray->step_x > 0)
            texture_index = 1;
        else
            texture_index = 3;
        return (save_texture_info(data, ray->vertical_distance, texture_index, ray->texture_x));
    }
    if (ray->map_y < 0 || ray->map_y >= data->map_length ||
        ray->map_x < 0 || ray->map_x >= data->map_width)
    {
        printf("DAA\n");
        return -1; // Выход за границы
    }
    
    ray->next_vertical_x += ray->step_x;
    ray->next_vertical_y += ray->step_y;
    return (0);
}

float handle_horizontal_intersection(t_data *data, Ray *ray)
{
    int texture_index;
     int map_y_offset;
     printf("80\n");
    
    if (handle_check(data, ray, 0) == -1)
        return (-1);
    printf("81\n");
    if (ray->step_y > 0)
        map_y_offset = 0;
    else
        map_y_offset = -1;
    if (data->new_map[ray->map_y + map_y_offset][ray->map_x] == '1')
    {   
        printf("82\n");
        if (ray->step_y > 0)
            texture_index = 2;
        else
            texture_index = 0;
        return (save_texture_info(data, ray->horizontal_distance, texture_index, ray->texture_y));
    }
    printf("83\n");
    ray->next_horizontal_x += ray->step_x;
    ray->next_horizontal_y += ray->step_y;
    return (0);
}

float trace_ray(t_data *data, float angle)
{
    Ray ray;
    int step_count = 0; // Добавим счетчик шагов
    const int max_steps = 1000; // Максимальное количество шагов

    printf("40\n");
    initialize_ray(data, &ray, angle);
    printf("41\n");

    while (step_count < max_steps) // Устанавливаем условие выхода
    {
        printf("42\n");

        calculate_next_intersection(data, &ray);
        printf("43\n");

        if (ray.vertical_distance < ray.horizontal_distance)
        {
            printf("44\n");
            float result = handle_vertical_intersection(data, &ray);
            if (result != 0)
                return (result);
        }
        else
        {
            printf("45\n");
            float result = handle_horizontal_intersection(data, &ray);
            if (result != 0)
                return (result);
        }

        step_count++; // Увеличиваем счетчик шагов
        printf("Шаг %d\n", step_count); // Отладка
    }

    printf("Максимальное количество шагов достигнуто, выход из цикла\n");
    return 0; // Если цикл завершился без нахождения пересечения
}
