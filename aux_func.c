#include "lem-in.h"


int kill_all(t_anthill *ah, int flag_all) {
	
	if (flag_all == 1) {
		for (int i = 0; i < ah->qrooms; i++) // Libera a memória alocada para o vetor de strings
			free(ah->sort_rooms[i]);
		free(ah->sort_rooms); // Libera a memória alocada para o vetor de strings
		
		free(ah->ants);
	}


    for (int i = 0; i < ah->qrooms; i++) 
        free(ah->rooms[i]);
    free(ah->rooms); 

	free(ah->se_rooms); 

	for (int i = 0; i < ah->qlinks; i++) 
        free(ah->links[i]);
	free(ah->links); 

	for (int i = 0; i < ah->qpaths; i++) 
        free(ah->paths[i]);
	free(ah->paths); 

	

    free(ah); 
    return 0;
}


void valid_msg(t_anthill *ah, int code) {
    
    const char *messages[] = { // Array of messages corresponding to codes
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
		kill_all(ah, 0);  
	}
    else 
        printf("Unknown validation code: %d\n", code);
}


void do_paths(t_anthill *ah, int matrix[N][N], int origin, int destiny, int visits[N], int i_path[], int index) {
	// Recursive function to generate all possible combinations of paths

    visits[origin] = 1;
    i_path[index] = origin;

    if (origin == destiny) {
		ah->qpaths++;
		//printf("index %d \n", index);
		ah->paths[ah->qpaths - 1] = (char *)malloc(((index + 2) * 2) * sizeof(char));  // Adjust size as needed
		ah->paths[ah->qpaths - 1][0] = '\0';
		for (int i = 0; i < index; i++) {
			//printf("%d ", i_path[i]);
			char temp[BUFFER_SIZE];
			ft_intToStr(i_path[i], temp);
            //sprintf(temp, "%d", i_path[i]);
            
            // Adds the element followed by a space, except for the last element
           if (ah->paths[ah->qpaths - 1][0] != '\0') {
				ft_strcat(ah->paths[ah->qpaths - 1], " ");
			}
			ft_strcat(ah->paths[ah->qpaths - 1], temp);
			//ah->paths[ah->qpaths] = ft_itoa(i_path[i]);
		}
		char temp[BUFFER_SIZE];
		ft_strcat(ah->paths[ah->qpaths - 1], " ");
		ft_intToStr(N - 1, temp);
		ft_strcat(ah->paths[ah->qpaths - 1], temp);
		//printf("\n");
    } else {
        for (int i = 0; i < N; i++) {
            if (matrix[origin][i] == 1 && !visits[i]) {
                do_paths(ah, matrix, i, destiny, visits, i_path, index + 1);
            }
        }
    }

    visits[origin] = 0; // Unselect current node when going back in recursion
}


void exclude_line(t_anthill* ah, int index) {
	free(ah->paths[index]);
    for (int i = index; i <  ah->qpaths - 1; i++)  // Shifting pointers to fill deleted line space
        ah->paths[i] = ah->paths[i + 1];
    ah->qpaths--; // Reducing the total number of paths
    ah->paths = (char **)realloc(ah->paths, ah->qpaths * sizeof(char *)); // Realloc to adjust pointer array size REM pode?
}


int find_room_index(char **rooms, int num_rooms, char *room_name) {
    for (int i = 0; i < num_rooms; i++) {
        if (strcmp(rooms[i], room_name) == 0) {
            return i;
        }
    }
    return -1; // Returns -1 if the room is not found
}


