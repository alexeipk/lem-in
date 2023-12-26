#include "gnl.h"
static int	treat_str_read(char *src, char **dst);
static int	newline_read(char **buffer, char **line, char *p_to_newline);
size_t	ft_strlen(const char *string);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);





int	get_next_line(int fd, char **line)
{
	char		str_read[BUFFER_SIZE + 1];
	static char	*buffer;
	ssize_t		from_read;
	char		*p_to_newline;

	if (&fd < 0 || !line)
		return (gnl_ERROR);
	from_read = 1;
	while (from_read > 0)
	{
		from_read = read(fd, str_read, BUFFER_SIZE);
		if (from_read < 0)
			return (gnl_ERROR);
		str_read[from_read] = '\0';
		if (!treat_str_read(str_read, &buffer) && from_read != 0)
			return (gnl_ERROR);
		p_to_newline = ft_strchr(buffer, '\n');
		if (p_to_newline != NULL)
			return (newline_read(&buffer, line, p_to_newline));
	}
	*line = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
	return (gnl_EOF);
}

static int	treat_str_read(char *src, char **dst)
{
	char	*tmp;

	tmp = NULL;
	if (*dst == NULL)
	{
		*dst = ft_strdup(src);
		if (!*dst)
		{
			free(src);
			return (gnl_ERROR);
		}
	}
	else
	{
		tmp = ft_strjoin(*dst, src);
		if (!tmp)
			return (gnl_ERROR);
		free(*dst);
		*dst = tmp;
	}
	return (NO_ERRORS);
}

static int	newline_read(char **buffer, char **line, char *p_to_newline)
{
	char	*tmp;
	int		len;

	len = p_to_newline - *buffer;
	*line = ft_substr(*buffer, 0, len);
	tmp = ft_strdup(&(*buffer)[len + 1]);
	free(*buffer);
	*buffer = tmp;
	return (gnl_READ);
}




size_t	ft_strlen(const char *string)
{
	size_t	count;

	count = 0;
	while (string[count])
		count++;
	return (count);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*final_str;
	int		counter;
	int		len_f_str;

	if (!s1 || !s2)
		return (NULL);
	len_f_str = (ft_strlen(s1) + ft_strlen(s2) + 1);
	final_str = (char *)malloc(sizeof(char) * len_f_str);
	if (final_str == NULL)
		return (NULL);
	counter = 0;
	while (*s1)
		final_str[counter++] = *s1++;
	while (*s2)
		final_str[counter++] = *s2++;
	final_str[counter] = '\0';
	return (final_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	counter;
	size_t	len_alloc;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < (size_t)start)
		len_alloc = 1;
	else if (len_s - (size_t)start > len)
		len_alloc = len;
	else
		len_alloc = len_s - (size_t)start;
	substr = (char *)malloc(sizeof(char) * (len_alloc + 1));
	if (substr == NULL)
		return (NULL);
	counter = 0;
	while (counter < len && (len_s > (size_t)(start + counter)))
	{
		substr[counter] = s[start + counter];
		counter++;
	}
	substr[counter] = '\0';
	return (substr);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	counter;

	counter = 0;
	if (c == '\0')
		return ((char *)(str + ft_strlen(str)));
	while (str[counter])
	{
		if (str[counter] == (unsigned char) c)
			return ((char *)&str[counter]);
		counter++;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		counter_src;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	counter_src = -1;
	while (src[++counter_src])
		dst[counter_src] = src[counter_src];
	dst[counter_src] = '\0';
	return (dst);
}
