#include <libc.h>

int gnc(char *str, char c)
{
    int i = 0;
	while (str[i] && str[i] != c)
    {
		if (str[i] == c)
            return (i);
		i++;
    }
    if(str[i] == c)
		return (i);
	return (-1);
}

void *ft_calloc(unsigned int n, int size)
{
	void *s;
	unsigned int total = n * size;
	if(!(s = malloc (total)))
		return (NULL);
	while (total-- > 0)
		*(unsigned char *)s++ = 0;
	return (s - size * n);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *join;
	if (!(join = (char *)malloc(sizeof(char) * (gnc(s1,'\0') + gnc(s2,'\0') + 1))))
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char *ft_substr(char *s, int start, int len)
{
    char *new;
    int i = 0;
    if(!(new = (char *)malloc(sizeof(char) * len + 1)))
        return (NULL);
    while (s[start] && len)
    {
        new[i] = s[start];
        i++;
        start++;
        len--;
    }
    new[i] = '\0';
    return (new);
}

int        get_next_line(int fd, char **line)
{
    static char *rest;
    char *buf;
    char *tmp;
    int ret;
    
    if(fd < 0 || !line || BUFFER_SIZE <= 0)
        return (-1);
    if (!rest && !(rest = ft_calloc(1, sizeof(char))))
        return (-1);
    if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
        return (-1);
    while (gnc(rest, '\n') < 0  && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[ret] = 0;
        rest = ft_strjoin(rest, buf);
    }
    free(buf);
    if (ret < 0)
        return (ret);
    *line = ft_substr(rest, 0, gnc(rest, '\n'));
    if (gnc(rest, '\n') < 0)
    {
        free(rest);
        return (0);
    }
    tmp = rest;
    rest = ft_substr(rest, gnc(rest, '\n') + 1, gnc(rest, '\0'));
    free(tmp);
    return (1);
    
}

int main(int ac, char **av)
{
    int ret;
    int fd = open(av[1], O_RDONLY);
    char *line;
    
    while ((ret = get_next_line(fd, &line)) > 0 )
    {
        printf("[%d] : %s\n", ret, line);
        free(line);
    }
    printf("[%d] : %s\n", ret, line);
    free(line);
}
