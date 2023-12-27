#include "lem-in.h"


int			main(void) {
	t_anthill	*ah;	//Assign anthill structure

	ah = (t_anthill *)malloc(sizeof(t_anthill));

	//Reset: initialize struct
	ah->ants = 0;

	//Print for tests, must be erase REM
	/*
	write(1, "Ants: ", 6);
	ft_putnbr(ah->ants);
	write(1, "\n", 1);
	*/

	int 	fd = STDIN_FILENO;  // Use STDIN_FILENO para ler da entrada padrão (teclado)
    char 	buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char 	linha[BUFFER_SIZE];
    ssize_t linhaIndex = 0;
	int 	row_just_numbers = 1;
	int		qtd_ants_file = 0;
	int 	mark_start = 0;
	int		mark_end = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            // Imprime caractere por caractere até encontrar uma quebra de linha
            if (buffer[i] == '\n') {
				if (row_just_numbers) 
					qtd_ants_file++; //printf("LINHA\n");  // Imprime a linha que contém apenas um número
                

				linha[linhaIndex] = '\0';  // Adiciona o caractere nulo para formar a string
                
				//if (ft_strnequ(*linha, "##start\n", 8))
				//	mark_start++;
				//printf("%d\n", (!ft_strcmp("##start\n", linha)));
				if (!ft_strncmp("##start", linha, 7))
					mark_start++;

				if (!ft_strncmp("##end", linha, 5))
					mark_end++;

				//printf("%s\n", linha);    // Imprime a linha
				ah->ants = ft_atoi(linha);
				row_just_numbers = 1;
                linhaIndex = 0;            // Reinicia o índice para a próxima linha
            } else {
                linha[linhaIndex++] = buffer[i];
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

	write(1, "Ants: ", 6);
	ft_putnbr(ah->ants);
	write(1, "\n", 1);

	free(ah);
	return 0;
}

