#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <string.h> 
#include <stdlib.h> // To malloc function
#include <unistd.h> // To write function
#include <stddef.h> // To size_t


#define BUFFER_SIZE 1000

typedef struct s_anthill {
	int 	qants;  	// qtd of ants
	int 	qrooms; 	// qtd of rooms
	char 	**rooms; 	// rooms list
	//char	*line;
}		t_anthill;


void			ft_putnbr(int n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int 			ft_count_spaces(const char *r);
int				ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
int 			kill_all(t_anthill *ah);
void 			valid_msg(t_anthill *ah, int code);
//static void		get_data(t_anthill *ah);


#endif