#include <stdio.h>
#include "windows.h"

#define g_szPipeName "\\\\.\\Pipe\\MyNamedPipe"  //Name given to the pipe
//Pipe name format - \\servername\pipe\pipename
//This pipe is for server on the same computer, however, pipes can be used to
//connect to a remote server

#define BUFFER_SIZE 1024 //1k
#define ACK_MESG_RECV "Message received successfully"



int pipeInit();
void pipeSend();
void pipeTerminate();