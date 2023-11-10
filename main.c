#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
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

int	ft_strlen(char *s)
{
	int i;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void ft_printnl()
{
	char nl;
	nl = '\n';
	write(1, &nl, 1);
}

void ft_printword(char *c)
{
	int	i;
	int length;
	i = 0;
	length = ft_strlen(c);
	while(i < length){
		write(1, &c[i], 1);
		i++;
	}
}

int	ft_in_array(char *haystack, char needle)
{
	int i;
	i = 0;
	while(haystack[i])
	{
		if (haystack[i] == needle)
			return (1);
		i++;
	}
	return (0);
}

char	*ofuscated_word(char *s, char *found_letters)
{
	int	len;
	char	*res;
	int	i;


	i = 0;
	len = ft_strlen(s);

	res = (char *) malloc(sizeof(char) * len);
	while(s[i])
	{
		if(ft_strlen(found_letters) > 0 && ft_in_array(found_letters, s[i]))
			res[i] = s[i];
		else
			res[i] = '*';
		i++;
	}
	return res;
}

char	ft_ask_letter()
{
	char letter;
	ft_printword("\nGive me a letter !\n");
	scanf(" %c", &letter);

	return (letter);
}

int ft_strcomp(char *str1, char *str2)
{
	int i = 0;
	int count = 0;

	while (str1[i]) {
		if (ft_in_array(str2, str1[i]))
			count++;
		i++;
	}
	if (count == ft_strlen(str1))
		return (1);
	return (0);
}

int	main(void){
	srand((unsigned int)time(NULL));

	int word_count = get_word_count();
	char **word_list = get_word_list(word_count);

	char	*word_to_guess = get_rendom_word(word_list, word_count);
	char	*res;
	char	found_letters[100];
	char	letter_guess;
	int	try;
	int max_try;

	max_try = ft_strlen(word_to_guess) + 3;
	try = 0;
	while (try <= max_try && !ft_strcomp(word_to_guess, found_letters))
	{
		
		letter_guess = ft_ask_letter();
		system("clear");
		if (!ft_in_array(found_letters, letter_guess))
			found_letters[try] = letter_guess;
		res = ofuscated_word(word_to_guess, found_letters);
		if(ft_in_array(word_to_guess, letter_guess))
		{
			printf("yes %c is in word_to_guess\n", letter_guess);
		}
		else
		{
			printf("no %c is not in word\n", letter_guess);
		}
		ft_printnl();
		ft_printword(res);

		try++;
	}
	if (ft_strcomp(word_to_guess, found_letters))
		printf("\nyou win!\n");
	else 
		printf("\nyou lose!\n");
}
