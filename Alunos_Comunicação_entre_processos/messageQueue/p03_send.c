/*
  Semelhante ao anterior, porém a caixa
  de mensagens envia continuamente 
	números inteiros.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#include "common.h"

#define QUEUE_NAME  "/test_queue_int"


int main(int argc, char **argv){
	mqd_t mq;
	int i=0;
	struct mq_attr attr;
	mq = mq_open(QUEUE_NAME, O_WRONLY);
	CHECK((mqd_t)-1 != mq);
	printf("Send to server (enter \"exit\" to stop it):\n");
	do {
		printf(": ");
		i++;
		CHECK(0 <= mq_send(mq, (char *) &i, sizeof(int), 0));
		CHECK( mq_getattr(mq, &attr) != -1);
		printf("%ld messages on queue.\n",attr.mq_curmsgs);
		sleep(2);
	} while (1);
	return 0;
}
