/*
  Semelhante ao anterior, porém a caixa
  de mensagens recebe continuamente 
	números inteiros.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#include "common.h"

#define QUEUE_NAME  "/test_queue_int"

int main(int argc, char **argv)
{
	mqd_t mq;
	struct mq_attr attr;
	int i; 
	int must_stop = 0;
	attr.mq_flags = 0; 
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(int);
	attr.mq_curmsgs = 0;
	mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
	CHECK((mqd_t)-1 != mq);
	do {
		ssize_t bytes_read;
		bytes_read = mq_receive(mq, (char  *) &i, sizeof(int), NULL);
		CHECK(bytes_read >= 0);
		printf("\nReceived: %d",i);
		sleep(3); 
	} while (1);
	return 0;
}
