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

	int 	fd = STDIN_FILENO;  // Use STDIN_FILENO to read input
    char 	buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char 	line[BUFFER_SIZE];
    ssize_t row_index = 0;
	int 	row_just_numbers = 1;
	int		qtd_ants_file = 0;
	int 	mark_start = 0;
	int		mark_end = 0;

	
    ah->rooms = (char**)malloc(sizeof(char*) * BUFFER_SIZE); // Inicializa o vetor de strings

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            // Build chars until find next line 
            if (buffer[i] == '\n') {
				if (row_just_numbers) 
					qtd_ants_file++; //printf("line\n");  // Imprime a line que contém apenas um número
                

				line[row_index] = '\0';  // Add null char to build string
                
				//if (ft_strnequ(*line, "##start\n", 8))
				//	mark_start++;
				//printf("%d\n", (!ft_strcmp("##start\n", line)));
				if (!ft_strncmp("##start", line, 7))
					mark_start++;

				if (!ft_strncmp("##end", line, 5))
					mark_end++;
				
				//printf("%d\n", ft_count_spaces(line));
				//printf("%d\n", ah->qrooms);
				if (ft_count_spaces(line) == 2){
					ah->rooms[ah->qrooms] = ft_strdup(line);
					ah->qrooms++;
				}

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

	//Validations
	if (qtd_ants_file == 0) {valid_msg(ah, 1); return 0;}
	if (qtd_ants_file > 1) {valid_msg(ah, 2); return 0;}
	if (mark_start == 0) {valid_msg(ah, 3); return 0;}
	if (mark_start > 1) {valid_msg(ah, 4); return 0;}
	if (mark_end == 0) {valid_msg(ah, 5); return 0;}
	if (mark_end > 1) {valid_msg(ah, 6); return 0;}
	if (ah->qrooms < 2) {valid_msg(ah, 7); return 0;}


	printf("Linhas com dois espaços:\n");
    for (int i = 0; i < ah->qrooms; i++) {
        printf("%s\n", ah->rooms[i]);
    }


	write(1, "Ants: ", 6);
	ft_putnbr(ah->qants);
	write(1, "\n", 1);

	
	write(1, "Rooms: ", 7);
	ft_putnbr(ah->qrooms);
	write(1, "\n", 1);

	kill_all(ah);
	return 0;
}

int kill_all(t_anthill *ah) {
    for (int i = 0; i < ah->qrooms; i++) // Libera a memória alocada para o vetor de strings
        free(ah->rooms[i]);
    free(ah->rooms); // Libera a memória alocada para o vetor de strings
    free(ah); // Libera a memória alocada para a estrutura principal
    return 0;
}


void valid_msg(t_anthill *ah, int code) {
    kill_all(ah);  


    const char *messages[] = { // Array de mensagens correspondentes aos códigos
        "There are no assigned ants on the map.",
        "Ants were assigned more than once on the map.",
        "There are no assigned start room on the map.",
        "Start room were assigned more than once on the map.",
        "There are no assigned end room on the map.",
        "End room were assigned more than once on the map.",
        "There must be at least 2 rooms on the map."
    };

    if (code >= 1 && code <= 7) 
        printf("\x1b[31mValidation flag: %s\x1b[0m\n", messages[code - 1]);
    else 
        printf("Unknown validation code: %d\n", code);
}
