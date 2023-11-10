#include <stdio.h>
#include <fcntl.h>
#include "stdlib.h"
#include <time.h>

char	*ft_strdup(char *src)
{
	char	*tmp;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	if (!(tmp = (char *)malloc(len + 1)))
		return (0);
	i = 0;
	while (src[i])
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int get_word_count()
{
    int fd;
    char buf[1];
    int word_count;

    word_count = 0;
    fd = open("list", O_RDONLY);
    
    while (read(fd, buf, 1))
        if (buf[0] == '\n')
            word_count++;
    close(fd);
    return word_count;
}



char* get_rendom_word(char** word_list,int word_count)
{
    srand((unsigned int)time(NULL));
    char *return_word;
    int index;

    index = 0;
    index = rand() % word_count;
    return_word = ft_strdup(word_list[index]);

    return return_word;
}

char **get_word_list(int word_count)
{
    int     i;
    int     fd;
    char    buf[1];
    char    **word_list;
    int     w_index;
    int     word_len;

    fd = open("list", O_RDONLY);
    w_index = 0;
    word_list = (char **)malloc(word_count * sizeof(char *));
    while (read(fd, buf, 1))
    {
        word_len = 0;
        if (buf[0] == '\n')
        {
            word_len++;
            word_list[w_index] = (char *)malloc(word_len * sizeof(char) + 1);
            w_index++;
        }
    }
    close(fd);
    fd = open("list", O_RDONLY);
    w_index = 0;
    i = 0;
    while(read(fd, buf, 1))
    {
        if (buf[0] != '\n')
        {
            word_list[w_index][i] = buf[0];
            i++;
        }
        else
        {
            word_list[w_index][i] = '\0';
            w_index++;
            i = 0;
        }
    }
    close(fd);
    return word_list;
}
