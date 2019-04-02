/*Source:
http://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
*/

/*Semelhante ao p01_receive.c, porém não sai do programa com o comando 'exit'.
  Observe o do{...}while(1)  */

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
	int continuar;//Utilizado no loop
	int must_stop = 0;
	attr.mq_flags = 0; 
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;
	mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
	CHECK((mqd_t)-1 != mq);
	do {
		ssize_t bytes_read;
		bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
		CHECK(bytes_read >= 0);
		buffer[bytes_read] = '\0';
		printf("Received: %s\n", buffer);
		sleep(5); 		
	} while (1);

	return 0;
}
