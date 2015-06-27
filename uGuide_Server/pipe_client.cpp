#include "pipe_client.h"

HANDLE hPipe;
char szBuffer[BUFFER_SIZE];

int pipeInit()
{
	//Connect to the server pipe using CreateFile()
	hPipe = CreateFile(
		g_szPipeName,   // pipe name 
		GENERIC_READ |  // read and write access 
		GENERIC_WRITE,
		0,              // no sharing 
		NULL,           // default security attributes
		OPEN_EXISTING,  // opens existing pipe 
		0,              // default attributes 
		NULL);          // no template file 

	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("\nError occurred while connecting to the server: %d", GetLastError());
		//One might want to check whether the server pipe is busy
		//This sample will error out if the server pipe is busy
		//Read on ERROR_PIPE_BUSY and WaitNamedPipe() for that
		return 1;  //Error
	}
	else
	{
		printf("\nCreateFile() was successful.");
	}
}

void pipeSend()
{
	printf("\nEnter a message to be sent to the server: ");
	gets(szBuffer);

	DWORD cbBytes;

	//Send the message to server
	BOOL bResult = WriteFile(
		hPipe,                // handle to pipe 
		szBuffer,             // buffer to write from 
		strlen(szBuffer) + 1,   // number of bytes to write, include the NULL
		&cbBytes,             // number of bytes written 
		NULL);                // not overlapped I/O 

	if ((!bResult) || (strlen(szBuffer) + 1 != cbBytes))
	{
		printf("\nError occurred while writing to the server: %d", GetLastError());
		CloseHandle(hPipe);
		return;  //Error
	}
	else
	{
		printf("\nWriteFile() was successful.");
	}

	//Read server response
	bResult = ReadFile(
		hPipe,                // handle to pipe 
		szBuffer,             // buffer to receive data 
		sizeof(szBuffer),     // size of buffer 
		&cbBytes,             // number of bytes read 
		NULL);                // not overlapped I/O 

	if ((!bResult) || (0 == cbBytes))
	{
		printf("\nError occurred while reading from the server: %d", GetLastError());
		CloseHandle(hPipe);
		return;  //Error
	}
	else
	{
		printf("\nReadFile() was successful.");
	}

	printf("\nServer sent the following message: %s", szBuffer);
}

void pipeTerminate()
{
	CloseHandle(hPipe);
}