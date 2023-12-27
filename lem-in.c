#include "lem-in.h"


int			main(void) {
	t_anthill	*ah;	//Assign anthill structure

	ah = (t_anthill *)malloc(sizeof(t_anthill));

	//Reset: initialize struct
	ah->qants = 0;
	ah->qrooms = 0;

	//Print for tests, must be erase REM
	/*
	write(1, "Ants: ", 6);
	ft_putnbr(ah->ants);
	write(1, "\n", 1);
	*/

	int 	fd = STDIN_FILENO;  // Use STDIN_FILENO para ler da entrada padrão (teclado)
    char 	buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char 	line[BUFFER_SIZE];
    ssize_t row_index = 0;
	int 	row_just_numbers = 1;
	int		qtd_ants_file = 0;
	int 	mark_start = 0;
	int		mark_end = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            // Imprime caractere por caractere até encontrar uma quebra de line
            if (buffer[i] == '\n') {
				if (row_just_numbers) 
					qtd_ants_file++; //printf("line\n");  // Imprime a line que contém apenas um número
                

				line[row_index] = '\0';  // Adiciona o caractere nulo para formar a string
                
				//if (ft_strnequ(*line, "##start\n", 8))
				//	mark_start++;
				//printf("%d\n", (!ft_strcmp("##start\n", line)));
				if (!ft_strncmp("##start", line, 7))
					mark_start++;

				if (!ft_strncmp("##end", line, 5))
					mark_end++;
				
				//printf("%d\n", ft_count_spaces(line));
				//printf("%d\n", ah->qrooms);
				if (ft_count_spaces(line) == 2)
					ah->qrooms++;

				//printf("%s\n", line);    // Imprime a line
				ah->qants = ft_atoi(line);
				row_just_numbers = 1;
                row_index = 0;            // Reinicia o índice para a próxima line
            } else {
                line[row_index++] = buffer[i];
				//printf("%d\n", buffer[i]);
				//printf("%d\n", ft_isdigit(buffer[i]));
				//if (buffer[i] != '\n' && buffer[i] != '\v' && buffer[i] != '\r' && buffer[i] != '\0') {
				if (buffer[i] > 31 && !ft_isdigit(buffer[i]))
						row_just_numbers = 0;
				//}
				//printf("%d\n", row_just_numbers);
				
            }
        }
    }


	if (qtd_ants_file == 0) {
		free(ah);
		printf("Validation flag: There are no assigned ants on the map.\n"); 
		return 0;
	}
	if (qtd_ants_file > 1) {
		free(ah);
		printf("Validation flag: Ants were assigned more than once on the map.\n"); 
		return 0;
	}
	if (mark_start == 0) {
		free(ah);
		printf("Validation flag: There are no assigned start room on the map.\n"); 
		return 0;
	}
	if (mark_start > 1) {
		free(ah);
		printf("Validation flag: start room were assigned more than once on the map.\n"); 
		return 0;
	}
	if (mark_end == 0) {
		free(ah);
		printf("Validation flag: There are no assigned end room on the map.\n"); 
		return 0;
	}
	if (mark_end > 1) {
		free(ah);
		printf("Validation flag: end room were assigned more than once on the map.\n"); 
		return 0;
	}


	//m->rooms = (char**)ft_memalloc(sizeof(char*) * (m->q_rooms + 1));

	write(1, "Ants: ", 6);
	ft_putnbr(ah->qants);
	write(1, "\n", 1);

	
	write(1, "Rooms: ", 7);
	ft_putnbr(ah->qrooms);
	write(1, "\n", 1);

	free(ah);
	return 0;
}

