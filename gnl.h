#ifndef GNL_H
# define GNL_H
#include <stdlib.h>
#include <unistd.h>
# define NO_ERRORS 1
enum e_returns
{
	gnl_ERROR = -1,
	gnl_EOF = 0,
	gnl_READ = 1,
};

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *string);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);

#endif