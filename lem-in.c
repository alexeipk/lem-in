#include "lem-in.h"

#include <stdio.h>
#include <stdlib.h> // Para a função malloc
#include <unistd.h> // To write function
#include <string.h>
#include <ctype.h> 

int			main(void) {
	t_anthill	*ah;

	ah = (t_anthill *)malloc(sizeof(t_anthill));
	//struct s_anthill ah = {0};
	ah->ants = 0;
	write(1, "Ants: ", 6);
	ft_putnbr(ah->ants);
	write(1, "\n", 1);


	int fd = STDIN_FILENO;  // Use STDIN_FILENO para ler da entrada padrão (teclado)
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char linha[BUFFER_SIZE];
    ssize_t linhaIndex = 0;
	int linhaContemApenasNumero = 1;
	int		qtd_ants_file = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            // Imprime caractere por caractere até encontrar uma quebra de linha
            if (buffer[i] == '\n') {
				if (linhaContemApenasNumero) {
                    //printf("LINHA\n");  // Imprime a linha que contém apenas um número
					qtd_ants_file++;
                }

				linha[linhaIndex] = '\0';  // Adiciona o caractere nulo para formar a string
                printf("%s\n", linha);    // Imprime a linha
				ah->ants = ft_atoi(linha);
				linhaContemApenasNumero = 1;
                linhaIndex = 0;            // Reinicia o índice para a próxima linha
            } else {
                linha[linhaIndex++] = buffer[i];
				//printf("%d\n", buffer[i]);
				//printf("%d\n", ft_isdigit(buffer[i]));
				//if (buffer[i] != '\n' && buffer[i] != '\v' && buffer[i] != '\r' && buffer[i] != '\0') {
				if (buffer[i] > 31 && !ft_isdigit(buffer[i]))
						linhaContemApenasNumero = 0;
				//}
				//printf("%d\n", linhaContemApenasNumero);
				
            }
        }
    }

	if (qtd_ants_file != 1) {
		free(ah);
		printf("There are more than 1 numbers of ants or nothing.\n"); 
		return 0;
	}

	write(1, "Ants: ", 6);
	ft_putnbr(ah->ants);
	write(1, "\n", 1);

	free(ah);
	return 0;
}

