/*Source:
http://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#include "common.h"

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

int main(int argc, char **argv){
	mqd_t mq;
	char buffer[MAX_SIZE];
	struct mq_attr attr;
	mq = mq_open(QUEUE_NAME, O_WRONLY);
	CHECK((mqd_t)-1 != mq);
	printf("Send to server (enter \"exit\" to stop it):\n");
	do{
		printf(": ");
		fflush(stdout);
		memset(buffer, 0, MAX_SIZE);
		fgets(buffer, MAX_SIZE, stdin);
		CHECK(0 <= mq_send(mq, buffer, MAX_SIZE, 0));
		CHECK( mq_getattr(mq, &attr) != -1);
		printf("%ld messages on queue.\n",attr.mq_curmsgs);
	}while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));
	/* Encerra a conexão com a fila */
	CHECK((mqd_t)-1 != mq_close(mq));
	return 0;
}
