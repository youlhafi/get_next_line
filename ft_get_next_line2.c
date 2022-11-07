#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
# define BUFFER_SIZE 10
char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        size_t  i;
        size_t  srclen;
        char    *str;

        if (!s)
                return (NULL);
        srclen = strlen(s);
        if (start > srclen)
                return (strdup(""));
        if (start + len > srclen)
                len = srclen - start;
        str = (char *)malloc(sizeof(char) * len + 1);
        if (!str)
                return (NULL);
        i = 0;
        while (s[start + i] && i < len)
        {
                str[i] = s[start + i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *str;
        int             i;
        int             j;
        size_t  size;

        if (!s1 || !s2)
                return (NULL);
        size = strlen(s1) + strlen(s2) + 1;
        str = (char *)malloc(sizeof(char) * size);
        if (!str)
                return (NULL);
        i = -1;
        while (s1[++i])
                str[i] = s1[i];
        j = -1;
        while (s2[++j])
                str[i + j] = s2[j];
        str[i + j] = '\0';
        return (str);
}


char	*ft_one_line(char *str, char **line)
{
	char *t;
	char *tmp;
	int i;

	i = 0;
	while(str[i] != '\n' && str[i] =='\0')
		i++;
	if (str[i] == '\n')
	{
		*line = ft_substr(str,0,i+1);
		tmp = strdup(&str[i+1]);
		free(str);
		str = tmp;
	}
	else
	{
		*line = ft_substr(str,0,i);
		free(str);
		str = NULL;
	}

	return (*line);
}

char	*ft_get_next_line(int fd)
{
	static char  *s;
	char *buff;
	char *tmp;
	char *line;
	int read_bytes;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (NULL);
	read_bytes = read(fd,buff,BUFFER_SIZE);
	while (read_bytes)
	{
		//read_bytes = read(fd,buff,BUFFER_SIZE);
		buff[read_bytes] = '\0';
		if (!s)
			s = strdup(buff);
		else
		{
			tmp = ft_strjoin(s,buff); //tmp should allocat in heap
			free(s);
			s = tmp;
		}
		if (strchr(s,'\n'))
			break ;
		read_bytes = read(fd,buff,BUFFER_SIZE);
	}
	return (ft_one_line(s,&line));
}

int main(void)
{
	int fd;
	fd = open("test",O_RDONLY);
	char *st;
	int j = 1;
	while (j < 5)
	{	
	st = ft_get_next_line(fd);
	printf("line [%d] : %s\n",j,st);
	j++;
	}
	return (0);
}
