#include "lem-in.h"



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




	write(1, "Links: ", 7);
	ft_putnbr(ah->qlinks);
	write(1, "\n", 1);
	
	for (int i = 0; i < ah->qlinks; i++) {
        printf("%s\n", ah->links[i]);
    }
	


	int matriz_de_caminhos[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0}
    };

    int origem = 0;
    int destino = N - 1;

    int visitados[N] = {0};
    int caminho[N];

    printf("Caminhos possíveis de %d para %d:\n", origem, destino);
    do_paths(ah, matriz_de_caminhos, origem, destino, visitados, caminho, 0);
    printf("Total de caminhos %d:\n", ah->qpaths);

	//removeDuplicatePaths(ah);

	for (int i = 0; i < ah->qpaths; i++) {
        printf("%s\n", ah->paths[i]);
    }

	for (int i = 0; i < ah->qpaths; i++) {
		int *vetor = NULL;
		// Usando strtok para dividir a string em tokens
		char *one = ft_strdup(ah->paths[i]);
		char *token = ft_strtok(one, " ");
		int indice = 0;

		// Convertendo cada token para um número inteiro e redimensionando o vetor
		while (token != NULL) {
			// Alocação inicial ou realocação do vetor
			vetor = (int *)realloc(vetor, (indice + 1) * sizeof(int));

			if (vetor == NULL) {
				fprintf(stderr, "Erro ao alocar memória.\n");
				exit(EXIT_FAILURE);
			}

			vetor[indice] = atoi(token);
			indice++;
			token = ft_strtok(NULL, " ");
		}

		// Iterando pelo vetor e imprimindo os valores
		for (int i = 0; i < indice; i++) {
			printf("%d\n", vetor[i]);
		}

		// Liberando a memória alocada
		free(vetor);
		free(one);
	}


/*
	for (int i = 0; i < ah->qpaths - 1; i++) {
        char *first_copy = ft_strdup(ah->paths[i]); 
        char *first = ft_strtok(first_copy, " ");
		int lfirst = 0;

		while (first != NULL) {
			lfirst++;
			first = ft_strtok(NULL, " ");
		}

		char *second_copy = ft_strdup(ah->paths[i + 1]); 
        char *second = ft_strtok(second_copy, " ");
		int lsecond = 0;

		while (second != NULL) {
			lsecond++;
			second = ft_strtok(NULL, " ");
		}

    	printf("Número de linhas (tokens): %d-%d\n", lfirst, lsecond);

		int maxnumb = (lfirst < lsecond) ? lfirst : lsecond;
		printf("Número de linhas %d\n", maxnumb);
        
		first = ft_strtok(first_copy, " ");
		second = ft_strtok(second_copy, " ");
		//printf("Valores de linhas (tokens): %c-%c\n", first[0], second[0]);

        for (int c = 0; c < maxnumb; c++) {
			if (first[c] != '\0' && second[c] != '\0') {
				printf("Valores de linhas (tokens): %c-%c\n", first[c], second[c]);
			} else {
				// Lida com a situação onde uma das strings é mais curta
				// ou onde '\0' é encontrado
				printf("Valores de linhas (tokens): -\n");
			}
		}

        // Liberar memória alocada
        free(first_copy);
		free(second_copy);
	}
	*/

	for (int i = 0; i < ah->qpaths; i++) {
        printf("%s\n", ah->paths[i]);
    }


	kill_all(ah);
	return 0;
}



/*
void removeDuplicatePaths(t_anthill* ah) {
    for (int i = 0; i < ah->qpaths - 1; i++) {
        for (int j = i + 1; j < ah->qpaths; j++) {
            // Comparando as linhas i e j
            if (strcmp(ah->paths[i], ah->paths[j]) == 0) {
                // Se as linhas são iguais, remova a menor delas
                // (você pode adicionar sua lógica para determinar qual é a menor)
                if (strlen(ah->paths[i]) > strlen(ah->paths[j])) {
                    // A linha j é menor, então podemos liberar a memória e definir para NULL
                    free(ah->paths[j]);
                    ah->paths[j] = NULL;
                } else {
                    // A linha i é menor ou ambas têm o mesmo comprimento, então liberamos a memória da linha i
                    free(ah->paths[i]);
                    ah->paths[i] = NULL;
                }
            }
        }
    }
}
*/




// Função recursiva para gerar todas as combinações possíveis de caminhos
void do_paths(t_anthill *ah, int matriz[N][N], int atual, int destino, int visitados[N], int caminho[], int index) {
    visitados[atual] = 1;
    caminho[index] = atual;

    if (atual == destino) {
		ah->qpaths++;
		//printf("index %d \n", index);
		ah->paths[ah->qpaths - 1] = (char *)malloc(((index + 2) * 2) * sizeof(char));  // Ajuste o tamanho conforme necessário
		ah->paths[ah->qpaths - 1][0] = '\0';
		for (int i = 0; i < index; i++) {
			//printf("%d ", caminho[i]);
			char temp[BUFFER_SIZE];
			ft_intToStr(caminho[i], temp);
            //sprintf(temp, "%d", caminho[i]);
            
            // Adiciona o elemento seguido por um espaço, exceto no último elemento
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

    visitados[atual] = 0; // Desmarca o nó atual ao retroceder na recursão
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





