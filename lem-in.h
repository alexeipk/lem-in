#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <string.h> 
#include <stdlib.h> // To malloc function
#include <unistd.h> // To write function
#include <stddef.h> // To size_t

#define BUFFER_SIZE 1000

typedef struct s_anthill {
	int 	ants; // qtd of ants
	char	*line;
}		t_anthill;


void			ft_putnbr(int n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

//static void		get_data(t_anthill *ah);


#endif