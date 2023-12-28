
#include <unistd.h> // To write function
#include <stdlib.h> // To malloc function
#include <stdio.h>


void	ft_putnbr(int n)
{
	char num;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else {
		if (n < 0) {
			write(1, "-", 1);
			n = n * -1;
		}
		if (n > 9) {
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else {
			num = n + '0';
			write(1, &num, 1);
		}
	}
}


int		ft_isdigit(int c) {
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


int	ft_atoi(const char *str) {
	int	index;
	int	sign;
	int	res;

	index = 0;
	sign = 1;
	res = 0;
	while (str[index] == ' ' || (str[index] >= '\t' && str[index] <= '\r'))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		res = (str[index] - '0') + (res * 10);
		index++;
	}
	return (res * sign);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n <= 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2 || n <= 0)
		return (0);
	if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	else
		return (0);
}

int ft_count_spaces(const char *r) {
    int count = 0;

    for (int i = 0; r[i] != '\0'; i++) {
        if (r[i] == ' ')
            count++;
    }

    return count;
}


int ft_count_hyphen(const char *r) {
    int count = 0;

    for (int i = 0; r[i] != '\0'; i++) {
        if (r[i] == '-')
            count++;
    }
    return count;
}

int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (s2 == NULL)
		return (NULL);
	if (s1[0] == '\0')
	{
		s2[0] = '\0';
		return (s2);
	}
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char *ft_strchr(const char *str, int ch) {
    while (*str != '\0' && *str != ch) {
        str++;
    }

    return (*str == ch) ? (char *)str : NULL;
}

char *ft_strtok(char *str, const char *delim) {
    static char *nextToken = NULL;

    if (str != NULL) {
        nextToken = str;
    } else if (nextToken == NULL) {
        return NULL; // Nada para tokenizar
    }

    // Encontrar o início do próximo token
    char *start = nextToken;
    while (*nextToken != '\0' && ft_strchr(delim, *nextToken) != NULL) {
        nextToken++;
    }

    if (*nextToken == '\0') {
        nextToken = NULL; // Nenhum token restante
        return NULL;
    }

    // Encontrar o fim do token
    //char *end = nextToken;
    while (*nextToken != '\0' && ft_strchr(delim, *nextToken) == NULL) {
        nextToken++;
    }

    if (*nextToken != '\0') {
        *nextToken = '\0'; // Terminar o token
        nextToken++;
    }

    return start;
}

/*
int	ft_size(int n)
{
	int	size;

	size = 1;
	if (n > 0)
		size = 0;
	return (size);
}

long	ft_abs(long n)
{
	long	abs;

	abs = n;
	if (n < 0)
		abs = -n;
	return (abs);
}

size_t	ft_size2(size_t size2, int nbr2)
{
	while (nbr2)
	{
		nbr2 /= 10;
		size2++;
	}
	return (size2);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	long	n;
	size_t	size;

	n = nbr;
	size = ft_size(nbr);
	n = ft_abs(n);
	size = ft_size2(size, nbr);
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	*(str + size--) = '\0';
	while (n > 0)
	{
		*(str + size--) = n % 10 + '0';
		n /= 10;
	}
	if (size == 0 && str[1] == '\0')
		*(str + size) = '0';
	else if (size == 0 && str[1] != '\0')
		*(str + size) = '-';
	return (str);
}*/

void ft_intToStr(int num, char *str) {
    int i = 0;

    // Lidar com o caso especial de 0
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // Lidar com números negativos
    if (num < 0) {
        str[i++] = '-';
        num = -num;
    }

    // Converter cada dígito do número para um caractere na string
    int divisor = 1;
    while (num / divisor > 9) {
        divisor *= 10;
    }

    while (divisor > 0) {
        int digit = num / divisor;
        str[i++] = digit + '0';
        num %= divisor;
        divisor /= 10;
    }

    // Adicionar o caractere nulo no final da string
    str[i] = '\0';
}


void ft_strcat(char *dest, const char *src) {
    // Encontrar o final da string de destino
    while (*dest != '\0') {
        dest++;
    }

    // Copiar os caracteres da string de origem para a string de destino
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    // Adicionar o caractere nulo no final da string de destino
    *dest = '\0';
}
