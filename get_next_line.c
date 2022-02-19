#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strjoin(char **str, char buf)
{
	int	i;
	char *tmp;
	i = 0;
	while ((*str)[i])
		i ++;
	tmp = (char*) malloc (sizeof(char) * (i + 2));
	if (!tmp)
		return (0);
	i = 0;
	while ((*str)[i])
	{
		tmp[i] = (*str)[i];
		i ++; 
	}	
	tmp[i] = buf;
	tmp[i + 1] = '\0';
	free(*str);
	(*str) = tmp;
	return(1);
}

int get_next_line(char **line)
{
	char buf;
	int ret;
	char *str;

	*line = (char *) malloc (sizeof(char));
	if (!line)
		return (-1);
	(*line)[0] = '\0';
	ret = read (0, &buf, 1);
	while(ret > 0)
	{
		if (buf == '\n')
			break;
		if(!ft_strjoin(line, buf))
		{
			free(*line);
			return (-1);
		}
		ret = read (0, &buf, 1);
	}
	// str = malloc(sizeof(char));
	// str[0]= '\0';
	return (ret);
}

int main()
{
	int flag;
	char *line;
	while((flag = get_next_line(&line)) > 0)
		free(line);
	free(line);
}
