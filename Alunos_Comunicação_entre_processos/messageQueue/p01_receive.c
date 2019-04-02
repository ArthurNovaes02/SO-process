/*FONTE:
http://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#include "common.h"

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

int main(int argc, char **argv)
{
	mqd_t mq;
	struct mq_attr attr;
	char buffer[MAX_SIZE + 1];
	int must_stop = 0;

	/* Inicializa os atributos da fila*/
	/*"0": o processo será bloqueado caso não haja 
	mensagens na fila. "O_NONBLOCK": a função de 
	leitura retorna código de erro e não é bloqueada.*/	
	attr.mq_flags = 0; 
	//Número máximo de mensagens na fila. 
	attr.mq_maxmsg = 10;
	//Tamanho máximo de cada mensagem.
	attr.mq_msgsize = MAX_SIZE;
	//Número de mensagens que estão atualmente na fila.
	attr.mq_curmsgs = 0;

	/* Abre a fila de mensagens.*/
	mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);

	//Continua a execução do programa se a condição 
	//abaixo for verdadeira.
	CHECK(mq !=(mqd_t)-1); //se (mq != -1)

	do {
		ssize_t bytes_read;
		/* Recebe a mensagem. O último parâmetro pode ser
		 usado para ler a prioridade da mensagem recebida.
		 Se a fila estiver vazia, o comando pode bloquear
		 o processo	ou retornar uma mensagem de erro 
		(dependendo do parâmetro: attr.mq_flags)*/
		bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
		CHECK(bytes_read >= 0);
		//Adiciona um '\0' ao final da mensagem lida.
		buffer[bytes_read] = '\0';

		//Verifica se a mensagem contém o texto "exit"
		if (! strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
			must_stop = 1;
		else
			//Exibe a mensagem recebida.
			printf("Received: %s\n", buffer);
		//O processo aguarda 5seg. para ler a próxima mensagem.
		sleep(5); 
	} while (!must_stop);
	//Fecha a fila. 
	CHECK((mqd_t)-1 != mq_close(mq));
	//Remove a fila.
	CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));
	return 0;
}
