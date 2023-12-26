#ifndef LEM_IN_H
# define LEM_IN_H


#define BUFFER_SIZE 1000

typedef struct s_anthill {
	int 	ants; // qtd of ants
	char	*line;
}		t_anthill;


void			ft_putnbr(int n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
//static void		get_data(t_anthill *ah);


#endif