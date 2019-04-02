/*Canal bidirecional - um único processo pode
enviar e receber mensagens.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#include "common.h"

#define QUEUE_NAME  "/test_queue_send_receive"

int main(int argc, char **argv)
{
	srand48(time(0));
	mqd_t mq;
	struct mq_attr attr;
	int i=0,opcao; 
	int must_stop = 0;
	attr.mq_flags = 0; 
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(int);
	attr.mq_curmsgs = 0;
	mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
	CHECK((mqd_t)-1 != mq);
	do {
		ssize_t bytes_read;
		printf("\nDigite (1) receber, (2) enviar, (3) sair: ");
		fflush(stdout);
		scanf("%d",&opcao);
		if (opcao==1){
			CHECK( mq_getattr(mq, &attr) != -1);
			if (attr.mq_curmsgs ==0)
				printf("\nCaixa de mensagem vazia - aguardando...");
			fflush(stdout);
			bytes_read = mq_receive(mq, (char  *) &i, sizeof(int), NULL);
			CHECK(bytes_read >= 0);
			CHECK( mq_getattr(mq, &attr) != -1);
			printf("\nRecebido: %d",i);	
		}
		else if(opcao==2){	
			CHECK( mq_getattr(mq, &attr) != -1);
			if (attr.mq_curmsgs ==10)
				printf("\nCaixa de mensagem cheia - aguardando...");
			fflush(stdout);
			CHECK(0 <= mq_send(mq, (char *) &i, sizeof(int), 0));				
			printf("\nEnviado: %d",i);	
			i++;
		}
		else if (opcao==3)
			break;
	} while (1);
	//Fecha a fila. 
	CHECK((mqd_t)-1 != mq_close(mq));
	//Remove a fila.
	//CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));
	return 0;
}
