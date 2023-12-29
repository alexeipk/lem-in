#include "lem-in.h"



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