#include "get_next_line.h"

char *find_line(char *line)
{
    int i;
    char *x;

    i = 0;
    if (!line||!line[i])
        return (NULL);
    while (line[i] && line[i] != '\n')
        i++;
    if (line[i] == '\n')
        i++;
    x = malloc(sizeof(char) * (i + 1));
    if (!x)
        return (NULL);
    i = 0;
    while(line[i] && line[i] != '\n')
    {
        x[i] = line[i];
        i++;
    }
    if (line[i] == '\n')
    {
        x[i] = line[i];
        i++;
    }
    x[i] = '\0';
    return (x);
}

char *delete_line( char *line)
{
    int i;
    int j;
    char *dup;
    if (!line)
        return (NULL);
    i = 0;
    while (line[i] && line[i] != '\n')
        i++;
    if (!line[i])
    {
        free(line);
        return (NULL);
    }    
    dup = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
    if (!dup)
        return (NULL);
    i++;
    j = 0;
    while (line[i])
        dup[j++] = line[i++];
    dup[j] = '\0';
    free(line);
    return (dup);
}

char *get_next_line(int fd)
{
    char *buffer;
    static char *line;
    int i;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return 0;

    i = 1;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    while(!ft_strchr(line, '\n') &&  i != 0)
    {
        i = read(fd ,buffer, BUFFER_SIZE);
        if (i == -1) 
        {
            free(buffer);
            return (NULL);
        }
        buffer[i] = '\0';
        line = ft_strjoin(line, buffer);
    }
    free(buffer);
    if (!line)
        return (NULL);
    buffer = find_line(line);
    line = delete_line(line);
    return (buffer);
}