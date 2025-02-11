/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:47:29 by mobonill          #+#    #+#             */
/*   Updated: 2025/02/06 20:06:53 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*char	*find_textures_paths(char *file, t_data *data)
{
	int		j;
	int		len;
	int		start;
	char	*txt;

	j = 0;
	len = 0;
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	j += 2;
	if (file[j] != '\t' && file[j] != ' ')
		err(data, ID_TXT);
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	if (file[j] == '\n' && file[j + 1] == '\0')
		return (err(data, ID_TXT), NULL);
	start = j;
	while (file[j])
	{
		len++;
		j++;
	}
	txt = ft_substr(file, start, len);
	printf("путь %s\n", txt);
	return (txt);
}*/
void extract_textures(t_data *data)
{
    int i = 0;

    while (data->file[i] && i < data->map_start)
    {
        if (ft_strncmp(data->file[i], "NO", 2) == 0 && !data->path_text[0])
            data->path_text[0] = find_textures_paths(data->file[i], data);
        else if (ft_strncmp(data->file[i], "SO", 2) == 0 && !data->path_text[1])
            data->path_text[1] = find_textures_paths(data->file[i], data);
        else if (ft_strncmp(data->file[i], "WE", 2) == 0 && !data->path_text[2])
            data->path_text[2] = find_textures_paths(data->file[i], data);
        else if (ft_strncmp(data->file[i], "EA", 2) == 0 && !data->path_text[3])
            data->path_text[3] = find_textures_paths(data->file[i], data);
        
        i++;
    }

    // Проверка, что все текстуры были загружены
    for (int j = 0; j < 4; j++)
    {
        if (data->path_text[j]) {
            printf("path texture for %s: %s\n", 
                j == 0 ? "NO" : j == 1 ? "SO" : j == 2 ? "WE" : "EA", 
                data->path_text[j]);
        } else {
            printf("Error: No texture path for %s\n", 
                j == 0 ? "NO" : j == 1 ? "SO" : j == 2 ? "WE" : "EA");
        }
    }
}

char *find_textures_paths(char *file, t_data *data)
{
    int j = 0;
    int len = 0;
    int start;
    char *txt;

    while (file[j] && (file[j] == '\t' || file[j] == ' '))
        j++;
    j += 2;  // Skip the "NO", "SO", etc.

    if (file[j] != '\t' && file[j] != ' ')
        err(data, ID_TXT);

    while (file[j] && (file[j] == '\t' || file[j] == ' '))
        j++;

    if (file[j] == '\n' || file[j] == '\0')
        return (err(data, ID_TXT), NULL);

    start = j;
    while (file[j]) {
        len++;
        j++;
    }

    txt = ft_substr(file, start, len);
    if (!txt)
        err(data, MALLOC);

    printf("Texture path: %s\n", txt);  // Debugging output

    return txt;
}


/*void	extract_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "NO", 2) == 0 && !data->no_txt)
			data->no_txt = find_textures_paths(data->file[i], data);
		else if (ft_strncmp(data->file[i], "SO", 2) == 0 && !data->so_txt)
			data->so_txt = find_textures_paths(data->file[i], data);
		else if (ft_strncmp(data->file[i], "WE", 2) == 0 && !data->we_txt)
			data->we_txt = find_textures_paths(data->file[i], data);
		else if (ft_strncmp(data->file[i], "EA", 2) == 0 && !data->ea_txt)
			data->ea_txt = find_textures_paths(data->file[i], data);
		i++;
	}
}*/





int	*find_rgb_colors(char *file, int *colors, int k, t_data *data)
{
	char	**save;
	char	*parsed;
	int		j;
	int		start;
	int		i;

	i = -1;
	save = ft_split(file, ',');
	colors = malloc(sizeof(int) * 3);
	while (save[++i])
	{
		j = skip_whitespaces(save, i, 0, &start);
		if ((j - start) > 0)
		{
			if ((j - start) > 3)
				error_color(colors, save, data);
			parsed = ft_substr(save[i], start, j - start);
			colors[k++] = ft_atoi(parsed);
			free(parsed);
		}
	}
	return (free_char_tab(save), colors);
}

void	extract_valid_colors(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "F", 1) == 0)
		{
			check_colors(data->file[i], data);
			data->f_color = find_rgb_colors(data->file[i],
					data->f_color, 0, data);
			color_is_valid(data->f_color, data);
		}
		else if (ft_strncmp(data->file[i], "C", 1) == 0)
		{
			check_colors(data->file[i], data);
			data->c_color = find_rgb_colors(data->file[i],
					data->c_color, 0, data);
			color_is_valid(data->c_color, data);
		}
		i++;
	}
}

/*bool	are_colors_and_textures_before_map(t_data *data, int j)
{
	int	i;

	i = -1;
	while (data->file[++i])
	{
		j = 0;
		while (data->file[i][j] == ' ' || data->file[i][j] == '\t')
			j++;
		if (data->file[i][j] == '1')
		{
			while (data->file[i][j] && (data->file[i][j] == '1'
				|| data->file[i][j] == ' ' || data->file[i][j] == '\t'
				|| data->file[i][j] == '\n'))
				j++;
			if (data->file[i][j] == '\0')
			{
				if (data->no_txt && data->so_txt && data->we_txt
					&& data->ea_txt && data->c_color && data->f_color)
					return (true);
				else
					return (false);
			}
		}
	}
	return (false);
}*/

bool are_colors_and_textures_before_map(t_data *data, int j)
{
    int i;

    i = -1;
    while (data->file[++i])
    {
        j = 0;
        
        // Пропускаем все пробелы и табуляции в начале строки
        while (data->file[i][j] == ' ' || data->file[i][j] == '\t')
            j++;

        // Если находим строку с картой (строка начинается с '1')
        if (data->file[i][j] == '1')
        {
            // Проверяем, что все текстуры и цвета определены
            if (data->path_text[0] && data->path_text[1] && data->path_text[2] && data->path_text[3] && data->c_color && data->f_color)
                return true;
            else
                return false;
        }

        // Проверка для строк с текстурами
        if (data->file[i][j] == 'N' && data->file[i][j + 1] == 'O' && data->file[i][j + 2] == ' ' && !data->path_text[0])
            data->path_text[0] = ft_strdup(&data->file[i][j + 3]);
        else if (data->file[i][j] == 'S' && data->file[i][j + 1] == 'O' && data->file[i][j + 2] == ' ' && !data->path_text[1])
            data->path_text[1] = ft_strdup(&data->file[i][j + 3]);
        else if (data->file[i][j] == 'W' && data->file[i][j + 1] == 'E' && data->file[i][j + 2] == ' ' && !data->path_text[2])
            data->path_text[2] = ft_strdup(&data->file[i][j + 3]);
        else if (data->file[i][j] == 'E' && data->file[i][j + 1] == 'A' && data->file[i][j + 2] == ' ' && !data->path_text[3])
            data->path_text[3] = ft_strdup(&data->file[i][j + 3]);
        
        // Проверка для цветов
        /*if (data->file[i][j] == 'F' && data->file[i][j + 1] == ' ' && !data->f_color)
            data->f_color = true;
        else if (data->file[i][j] == 'C' && data->file[i][j + 1] == ' ' && !data->c_color)
            data->c_color = true;*/
    }

    return false; // Если файл закончился, а текстуры и цвета были найдены до карты, возвращаем false
}

