#include "lem-in.h"

//int N = 0;

int			main(void) {
	t_anthill	*ah;	//Assign anthill structure

	ah = (t_anthill *)malloc(sizeof(t_anthill));

	//Reset: initialize struct
	ah->qants = 0;
	ah->qrooms = 0;
	ah->qlinks = 0;
	ah->qpaths = 0;

	
    ah->rooms = (char**)malloc(sizeof(char*) * BUFFER_SIZE); // Inicializa o vetor de strings
	ah->se_rooms = (char**)malloc(sizeof(char*) * BUFFER_SIZE); // Inicializa o vetor de strings
	ah->links = (char**)malloc(sizeof(char*) * BUFFER_SIZE); // Inicializa o vetor de strings
	ah->paths = (char**)malloc(sizeof(char*) * BUFFER_SIZE); // Inicializa o vetor de strings

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
					//if (previous_start_end == 1)
					//	ah->start_room = ft_strdup(line);
					//if (previous_start_end == 2)
					//	ah->end_room = ft_strdup(line);
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
				//}
				//printf("%d\n", row_just_numbers);
				
            }
        }
    }

	//N = 4;

	
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
	char **sort_rooms = (char**)malloc(sizeof(char*) * ah->qrooms);
	for (int i = 0; i < ah->qrooms; i++) {
        if (ft_atoi(ah->se_rooms[i]) == 1) {
			char *temp = strdup(ah->rooms[i]);
			char *first = strtok(temp, " ");
			sort_rooms[0] = strdup(first);
			free(temp); 
			break; 
		}
    }
	int index_sort = 1;
	for (int i = 0; i < ah->qrooms; i++) {
        if (ft_atoi(ah->se_rooms[i]) == 0) {
			char *temp = strdup(ah->rooms[i]);
			char *first = strtok(temp, " ");
			sort_rooms[index_sort] = strdup(first);
			index_sort++;
			free(temp); 
		}
    }
	for (int i = 0; i < ah->qrooms; i++) {
        if (ft_atoi(ah->se_rooms[i]) == 2) {
			char *temp = strdup(ah->rooms[i]);
			char *first = strtok(temp, " ");
			sort_rooms[ah->qrooms - 1] = strdup(first);
			free(temp); 
		}
    }
	for (int i = 0; i < ah->qrooms; i++) printf("Sort rooms: %s\n", sort_rooms[i]);




	write(1, "Links: ", 7);
	ft_putnbr(ah->qlinks);
	write(1, "\n", 1);
	
	for (int i = 0; i < ah->qlinks; i++) {
        printf("%s\n", ah->links[i]);
    }




	
	

	/*int matriz_de_caminhos[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0}
    };*/
	int matriz_de_caminhos[N][N] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
    };
	//N = 4;

    int origem = 0;
    int destino = N - 1;

    int visitados[N] = {0};
    int caminho[N];

    printf("Caminhos possíveis de %d para %d:\n", origem, destino);
    do_paths(ah, matriz_de_caminhos, origem, destino, visitados, caminho, 0);
    printf("Total de caminhos %d:\n", ah->qpaths);

	for (int i = 0; i < ah->qpaths; i++) {
        printf("%s\n", ah->paths[i]);
    }



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
	printf("Total de caminhos %d:\n", ah->qpaths);
	for (int i = 0; i < ah->qpaths; i++) {
        printf("%s\n", ah->paths[i]);
    }


	for (int i = 0; i < ah->qrooms; i++) // Libera a memória alocada para o vetor de strings
        free(sort_rooms[i]);
    free(sort_rooms); // Libera a memória alocada para o vetor de strings
	kill_all(ah);

	return 0;
}



void exclude_line(t_anthill* ah, int index) {
	free(ah->paths[index]);
    for (int i = index; i <  ah->qpaths - 1; i++)  // Shifting pointers to fill deleted line space
        ah->paths[i] = ah->paths[i + 1];
    ah->qpaths--; // Reducing the total number of paths
    ah->paths = (char **)realloc(ah->paths, ah->qpaths * sizeof(char *)); // Realloc to adjust pointer array size REM pode?
}



void do_paths(t_anthill *ah, int matriz[N][N], int atual, int destino, int visitados[N], int caminho[], int index) {
	// Recursive function to generate all possible combinations of paths

    visitados[atual] = 1;
    caminho[index] = atual;

    if (atual == destino) {
		ah->qpaths++;
		//printf("index %d \n", index);
		ah->paths[ah->qpaths - 1] = (char *)malloc(((index + 2) * 2) * sizeof(char));  // Adjust size as needed
		ah->paths[ah->qpaths - 1][0] = '\0';
		for (int i = 0; i < index; i++) {
			//printf("%d ", caminho[i]);
			char temp[BUFFER_SIZE];
			ft_intToStr(caminho[i], temp);
            //sprintf(temp, "%d", caminho[i]);
            
            // Adds the element followed by a space, except for the last element
           if (ah->paths[ah->qpaths - 1][0] != '\0') {
				ft_strcat(ah->paths[ah->qpaths - 1], " ");
			}
			ft_strcat(ah->paths[ah->qpaths - 1], temp);
			//ah->paths[ah->qpaths] = ft_itoa(caminho[i]);
		}
		char temp[BUFFER_SIZE];
		ft_strcat(ah->paths[ah->qpaths - 1], " ");
		ft_intToStr(N - 1, temp);
		ft_strcat(ah->paths[ah->qpaths - 1], temp);
		//printf("\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (matriz[atual][i] == 1 && !visitados[i]) {
                do_paths(ah, matriz, i, destino, visitados, caminho, index + 1);
            }
        }
    }

    visitados[atual] = 0; // Unselect current node when going back in recursion
}
















int kill_all(t_anthill *ah) {
    for (int i = 0; i < ah->qrooms; i++) // Libera a memória alocada para o vetor de strings
        free(ah->rooms[i]);
    free(ah->rooms); // Libera a memória alocada para o vetor de strings

	//for (int i = 0; i < ah->qrooms; i++) // Libera a memória alocada para o vetor de strings
    //    free(ah->se_rooms[i]);
    free(ah->se_rooms); // Libera a memória alocada para o vetor de strings

	
	for (int i = 0; i < ah->qlinks; i++) // Libera a memória alocada para o vetor de strings
        free(ah->links[i]);
	free(ah->links); // Libera a memória alocada para o vetor de strings

	for (int i = 0; i < ah->qpaths; i++) // Libera a memória alocada para o vetor de strings
        free(ah->paths[i]);
	free(ah->paths); // Libera a memória alocada para o vetor de strings
	//free(ah->start_room); 
	//free(ah->end_room); 

    free(ah); // Libera a memória alocada para a estrutura principal
    return 0;
}


void valid_msg(t_anthill *ah, int code) {
    
    const char *messages[] = { // Array de mensagens correspondentes aos códigos
        "There are no assigned ants on the map.",
        "Ants were assigned more than once on the map.",
        "There are no assigned start room on the map.",
        "Start room were assigned more than once on the map.",
        "There are no assigned end room on the map.",
        "End room were assigned more than once on the map.",
        "There must be at least 2 rooms on the map.",
		"Rooms were assigned more than once on the map."
    };

    if (code >= 1 && code <= 8) {
        printf("\x1b[31mValidation flag: %s\x1b[0m\n", messages[code - 1]);
		kill_all(ah);  
	}
    else 
        printf("Unknown validation code: %d\n", code);
}





