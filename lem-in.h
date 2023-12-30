#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <string.h> 
#include <stdlib.h> // To malloc function
#include <unistd.h> // To write function
#include <stddef.h> // To size_t
#include <stdbool.h> // To boolean

#define N 4 // Número total de nós, deve ser mudado para dinamico REM
//extern int N;
//existem muitas funcoes no C que precisam ser substituidas que no libft nao estavam boas


#define BUFFER_SIZE 4096

typedef struct Ant {
    int 		currentRoom;
} 				t_ant;

typedef struct 	s_anthill {
	int 		qants;  	// qtd of ants
	t_ant 		*ants; 		// Ants vector
	int 		qrooms; 	// qtd of rooms
	char 		**rooms; 	// rooms list
	char 		**se_rooms;	// start and end rooms list index
	char 		**sort_rooms;
	int 		qlinks; 	// qtd of links
	char 		**links; 	// links list
	int 		qpaths; 	// qtd of paths
	char 		**paths; 	// path list
}				t_anthill;


void			ft_putnbr(int n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int 			ft_count_spaces(const char *r);
int 			ft_count_hyphen(const char *r);
int				ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char 			*ft_strchr(const char *str, int ch);
char 			*ft_strtok(char *str, const char *delim);
size_t 			ft_strcspn(const char *str, const char *delim);
char 			*ft_strtok_r(char *str, const char *delim, char **saveptr);

//char	*ft_itoa(int nbr);
void 			ft_intToStr(int num, char *str);
void			ft_strcat(char *dest, const char *src);

int valid_input(t_anthill *ah);
int 			kill_all(t_anthill *ah, int flag_all);
void 			valid_msg(t_anthill *ah, int code);
void 			do_paths(t_anthill *ah, int matrix[N][N], int origin, int destiny, int visits[N], int i_path[], int index);
void 			exclude_line(t_anthill* ah, int index);
int 			find_room_index(char **rooms, int num_rooms, char *room_name);
void 			moveAnts(t_anthill *ah);

//static void		get_data(t_anthill *ah);


#endif