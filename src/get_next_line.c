#include "../inc/get_next_line.h"

static char	*ft_read_line(int fd, char *save)
{
    char	*buf;
    int		read_bytes;

    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    read_bytes = 1;
    while (read_bytes > 0 && !ft_strchr(save, '\n'))
    {
        read_bytes = read(fd, buf, BUFFER_SIZE);
        if (read_bytes == -1)
        {
            free(buf);
            return (NULL);
        }
        buf[read_bytes] = '\0';
        save = ft_strjoin(save, buf);
    }
    free(buf);
    return (save);
}

static char	*ft_get_line(char *save)
{
    char	*line;
    int		i;

    i = 0;
    if (!save[i])
        return (NULL);
    while (save[i] && save[i] != '\n')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while (save[i] && save[i] != '\n')
    {
        line[i] = save[i];
        i++;
    }
    if (save[i] == '\n')
    {
        line[i] = save[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

static char	*ft_save(char *save)
{
    char	*new_save;
    int		i;
    int		j;

    i = 0;
    while (save[i] && save[i] != '\n')
        i++;
    if (!save[i])
    {
        free(save);
        return (NULL);
    }
    new_save = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
    if (!new_save)
        return (NULL);
    i++;
    j = 0;
    while (save[i])
        new_save[j++] = save[i++];
    new_save[j] = '\0';
    free(save);
    return (new_save);
}

char	*get_next_line(int fd)
{
    static char	*save;
    char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    save = ft_read_line(fd, save);
    if (!save)
        return (NULL);
    line = ft_get_line(save);
    save = ft_save(save);
    return (line);
} 