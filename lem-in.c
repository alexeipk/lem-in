#include "lem-in.h"

//int N = 0;

int			main(void) {
	t_anthill	*ah;	// Assign anthill structure

	ah = (t_anthill *)malloc(sizeof(t_anthill));

	//Reset: initialize struct
	ah->qants = 0;
	ah->qrooms = 0;
	ah->qlinks = 0;
	ah->qpaths = 0;

    ah->rooms = (char**)malloc(sizeof(char*) * BUFFER_SIZE); 	// Inicializa o vetor de strings
	ah->se_rooms = (char**)malloc(sizeof(char*) * BUFFER_SIZE); // Inicializa o vetor de strings
	ah->links = (char**)malloc(sizeof(char*) * BUFFER_SIZE); 	// Inicializa o vetor de strings
	ah->paths = (char**)malloc(sizeof(char*) * BUFFER_SIZE); 	// Inicializa o vetor de strings

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
	int 	previous_start_end = 0;

	//parse file and insert values into struct
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) { // Build chars until find next line 
            if (buffer[i] == '\n') {
				if (row_just_numbers) // Find numeric row -> number of ants
					qtd_ants_file++; 
                
				line[row_index] = '\0';  // Add null char to build string
                
				if (!ft_strncmp("##start", line, 7)) { // Find row with ##start
					mark_start++;
					previous_start_end = 1;
				}

				if (!ft_strncmp("##end", line, 5)) { // Find row with ##end
					mark_end++;
					previous_start_end = 2;
				}

				//printf("%d\n", ft_count_spaces(line));
				//printf("%d\n", ah->qrooms);
				if (ft_count_spaces(line) == 2){ // Find row with 2 spaces, REM 2nd and 3rd elements must be numerics or not begin with ##
					ah->rooms[ah->qrooms] = ft_strdup(line);

					ah->se_rooms[ah->qrooms] = "0";
					if (previous_start_end == 1) {
						ah->se_rooms[ah->qrooms] = "1";
						previous_start_end = 0;
					}
					if (previous_start_end == 2) {
						ah->se_rooms[ah->qrooms] = "2";
						previous_start_end = 0;
					}
					ah->qrooms++;
				}

				if (ft_count_hyphen(line) == 1){ // Find row with hyfen
					ah->links[ah->qlinks] = ft_strdup(line);
					ah->qlinks++;
				}

				//printf("%s\n", line);    
				ah->qants = ft_atoi(line);
				row_just_numbers = 1;	// Reset row just numbers
                row_index = 0;          // Reset index to next line
            } else {
                line[row_index++] = buffer[i];
				//printf("%d\n", buffer[i]);
				//printf("%d\n", ft_isdigit(buffer[i]));
				//if (buffer[i] != '\n' && buffer[i] != '\v' && buffer[i] != '\r' && buffer[i] != '\0') {
				if (buffer[i] > 31 && !ft_isdigit(buffer[i]))
						row_just_numbers = 0;
				//printf("%d\n", row_just_numbers);	
            }
        }
    }

	//N = 4;

	//Ver sem rooms, sem formigas, sem inicio ou fim, sem solucao possivel, outros comentarios, 
	//Validations
	if (qtd_ants_file == 0) {valid_msg(ah, 1); return 0;}
	if (qtd_ants_file > 1) {valid_msg(ah, 2); return 0;}
	if (mark_start == 0) {valid_msg(ah, 3); return 0;}
	if (mark_start > 1) {valid_msg(ah, 4); return 0;}
	if (mark_end == 0) {valid_msg(ah, 5); return 0;}
	if (mark_end > 1) {valid_msg(ah, 6); return 0;}
	if (ah->qrooms < 2) {valid_msg(ah, 7); return 0;}

	for (int i = 0; i < ah->qrooms - 1; i++) {
		char *first_copy = ft_strdup(ah->rooms[i]); 
    	char *first = ft_strtok(first_copy, " ");
		
		for (int j = i + 1; j < ah->qrooms; j++) {
			char *second_copy = ft_strdup(ah->rooms[j]); 
        	char *second = ft_strtok(second_copy, " ");

			//printf("%s-%s\n", first, second);
			if (first[0] == second[0]) {
				valid_msg(ah, 8); 
				free(first_copy);
            	free(second_copy);
				return 0;
			}
			free(second_copy);
		}
		free(first_copy);
    }



	//Prints
	//write(1, "Ants: ", 6);
	ft_putnbr(ah->qants);
	write(1, "\n", 1);



	
	/*
	write(1, "Rooms: ", 7);
	ft_putnbr(ah->qrooms);
	write(1, "\n", 1);
*/
	/*
    for (int i = 0; i < ah->qrooms; i++) {
        printf("%s\n", ah->rooms[i]);
    }
	for (int i = 0; i < ah->qrooms; i++) {
        printf("%s\n", ah->se_rooms[i]);
    }*/

	for (int i = 0; i < ah->qrooms; i++) {
        if (ft_atoi(ah->se_rooms[i]) == 1) {
			write(1, "##start\n", 8);
			printf("%s\n", ah->rooms[i]);
		}
    }
	for (int i = 0; i < ah->qrooms; i++) {
        if (ft_atoi(ah->se_rooms[i]) == 2) {
			write(1, "##end\n", 6);
			printf("%s\n", ah->rooms[i]);
		}
    }
	for (int i = 0; i < ah->qrooms; i++) {
        if (ft_atoi(ah->se_rooms[i]) == 0) {
			printf("%s\n", ah->rooms[i]);
		}
    }

	//Do rooms sort: start - other - end
	ah->sort_rooms = (char **)malloc(sizeof(char *) * ah->qrooms);
	int index_sort = 0;
	for (int i = 0; i < ah->qrooms; i++) {
		char *temp = ft_strdup(ah->rooms[i]);
		char *first = strtok(temp, " ");

		if (ft_atoi(ah->se_rooms[i]) == 1) 
			ah->sort_rooms[0] = ft_strdup(first);  
		else if (ft_atoi(ah->se_rooms[i]) == 0) 
			ah->sort_rooms[++index_sort] = ft_strdup(first);  
		else if (ft_atoi(ah->se_rooms[i]) == 2) 
			ah->sort_rooms[ah->qrooms - 1] = ft_strdup(first); 
		free(temp);
	}
	for (int i = 0; i < ah->qrooms; i++) printf("Sort rooms: %s\n", ah->sort_rooms[i]);




	// Put all ants into start room
	ah->ants = (t_ant *)malloc(ah->qants * sizeof(t_ant));
	for (int i = 0; i < ah->qants; i++) {
		ah->ants[i].currentRoom = 0;
        printf("Formiga %d está na sala %d\n", i + 1, ah->ants[i].currentRoom);
    }
	




	//write(1, "Links: ", 7);
	ft_putnbr(ah->qlinks);
	write(1, "\n", 1);
	for (int i = 0; i < ah->qlinks; i++) printf("%s\n", ah->links[i]);





	// Criar matrix de i_paths com base nas informações dos quartos ordenados e nos i_paths encontrados
	int path_matrix[N][N] = {0}; // Inicializa a matrix com zeros

	// Preenche a matrix com base nos links
	for (int i = 0; i < ah->qlinks; i++) {
		char *link_copy = ft_strdup(ah->links[i]);
		char *room1 = ft_strtok(link_copy, "-");
		char *room2 = ft_strtok(link_copy, "-");

		// Encontra os índices correspondentes aos quartos em ah->sort_rooms
		int index1 = -1, index2 = -1;
		for (int j = 0; j < ah->qrooms; j++) {
			//printf("Sort rooms: %s %d\n", ah->sort_rooms[j],  ft_strlen(ah->sort_rooms[j]));
			//printf("room1 : %s %d\n", room1, ft_strlen(room1));
			//printf("room2 : %s %d\n", room2, ft_strlen(room2));
			if (strcmp(ah->sort_rooms[j], room1) == 0) 
				index1 = j;
			
			if (strcmp(ah->sort_rooms[j], room2) == 0) 
				index2 = j;
		}
		//printf("%d\n", index1);
		//printf("%d\n", index2);

		// Marca a matrix de i_paths com 1 para indicar um link
		if (index1 != -1 && index2 != -1) {
			path_matrix[index1][index2 + 1] = 1;
			//path_matrix[index2][index1] = 1; // Considerando que a matrix é simétrica
		}

		free(link_copy);
	}

	// Imprime a matrix de i_paths
	/**/
	printf("matrix de i_paths:\n");
	for (int i = 0; i < ah->qrooms; i++) {
		for (int j = 0; j < ah->qrooms; j++) printf("%d ", path_matrix[i][j]);
		printf("\n");
	}


	/*int path_matrix[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0}
    };*/
	/*int path_matrix[N][N] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
    };*/
	//N = 4;

    int origem = 0;
    int destiny = N - 1;

    int visits[N] = {0};
    int i_path[N];
	

    printf("i_paths possíveis de %s para %s:\n", ah->sort_rooms[0], ah->sort_rooms[ah->qrooms - 1]);
    do_paths(ah, path_matrix, origem, destiny, visits, i_path, 0);
    printf("Total de i_paths %d:\n", ah->qpaths);

	for (int i = 0; i < ah->qpaths; i++) printf("%s\n", ah->paths[i]);


	write(1,"---\n", 4);

	//	printf("%s-%s\n", ah->paths[ref], ah->paths[ref + 1]);

	//removeDuplicatePaths(ah);
	int ref = 0;
	while (ref < ah->qpaths - 1) {
		int *v1 = NULL; char *l1 = ft_strdup(ah->paths[ref]); 	  char *saveptr1; char *t1 = strtok_r(l1, " ", &saveptr1); int i1 = 0;
		int *v2 = NULL; char *l2 = ft_strdup(ah->paths[ref + 1]); char *saveptr2; char *t2 = strtok_r(l2, " ", &saveptr2); int i2 = 0;

		// Converting each token to an integer and resizing the vector
		while (t1 != NULL) {
			v1 = (int *)realloc(v1, (i1 + 1) * sizeof(int));
			v1[i1] = atoi(t1);
			t1 = strtok_r(NULL, " ", &saveptr1);
			i1++;
		}
		while (t2 != NULL) {
			v2 = (int *)realloc(v2, (i2 + 1) * sizeof(int));
			v2[i2] = atoi(t2);
			t2 = strtok_r(NULL, " ", &saveptr2);
			i2++;
		}

		int max_iter = i1 < i2 ? i1 : i2;
		//printf("i1:%d - i2:%d - maxiter:%d\n", i1, i2, max_iter);

		for (int i = 1; i < max_iter - 1; i++) {
			if (v1[i] == v2[i]){
				if (i1 > i2) {
					exclude_line(ah, ref);
					printf("apagar v1\n");		
					ref = -1;	
					break;		
				} else {
					exclude_line(ah, ref + 1);
					printf("apagar v2\n");
					ref = -1;
					break;
				}
			}
			//printf("index %d: %d\n", i1, v1[i]);
		}

		free(v1); free(l1);
		free(v2); free(l2);

		ref++;
	}

	write(1,"---\n", 4);
	printf("Total de i_paths %d:\n", ah->qpaths);
	for (int i = 0; i < ah->qpaths; i++) {
        printf("%s\n", ah->paths[i]);
    }

	


	moveAnts(ah);




	

	kill_all(ah, 1);

	return 0;
}


void moveAnts(t_anthill *ah) {
    // Implemente a lógica de movimentação das formigas aqui
    // Use a lista de caminhos (i_path) e atualize a posição das formigas
    // Imprima os movimentos conforme as formigas se movem
    // Considere que em cada sala só pode haver uma formiga

	

	for (int i = 0; i < ah->qpaths; i++) {
        printf("%s\n", ah->paths[i]);
    }


}