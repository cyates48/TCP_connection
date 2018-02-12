 /**************************
 *     Christopher Yates
 *     Thursday, 2:15-5
 *     server.c
 *     Short Desciption: This is the server.c program. The file
 *     		doesn't take any intial arguments. It waits for 
 *     		the client to send out a signal to connect, and
 *     		once they are connected, the server receives the
 *     		name of the output file. It opens the output file,
 *     		and then it begins to write the data that is being
 *     		read from the input file on the client side.
 *
 ***************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main (int, char *[]); 


/*********************
 * main
 *********************/
int main (int argc, char *argv[])
{
	int	n;
	char *p; 
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr; 
	char buff[10];
	FILE *out;

	// set up
	memset (&serv_addr, '0', sizeof (serv_addr));
	memset (buff, '0', sizeof (buff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	serv_addr.sin_port = htons (5000); 

	// create socket, bind, and listen
	listenfd = socket (AF_INET, SOCK_STREAM, 0);
	bind (listenfd, (struct sockaddr*)&serv_addr, sizeof (serv_addr)); 
	listen (listenfd, 10); 

	// accept and interact
	connfd = accept (listenfd, (struct sockaddr*)NULL, NULL); 
	
	// recieve filename and open output file
	if (read(connfd, buff, sizeof (buff)) > 0)
		out = fopen(buff, "wb");		
			
	// receive data and reply
	while ((n = read (connfd, buff, sizeof (buff))) > 0)
	{
		fwrite(buff,1,n,out);
	}

	close (connfd);

}
