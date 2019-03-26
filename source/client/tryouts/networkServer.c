#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/un.h>

#define BUFFER 1024

int main(void)
{
	int port = 65432;
	char data[BUFFER];
	struct sockaddr_in dir;
	struct sockaddr client;
	socklen_t long_client;
	int id, idReuse=1, son, aux;
	
	memset(&dir,0,sizeof(dir));
	dir.sin_port = htons(port);
	dir.sin_family = AF_INET;
	dir.sin_addr.s_addr = INADDR_ANY;

	printf("Creating socket... ");
	id = socket(AF_INET, SOCK_STREAM, 0);
	if (id == -1)
		return -1;
	printf("done!\n");

	printf("Configuring socket... ");
	if(setsockopt(id,SOL_SOCKET,SO_REUSEADDR,&idReuse,sizeof(idReuse))==-1)
	   return -1;
	printf("done!\n");

	printf("Binding... ");
	if(bind(id, (struct sockaddr *)&dir, sizeof(dir)) == -1)
	{
		close (id);
		return -1;
	}
	printf("done!\n");

	printf("Listening... ");
	if (listen(id , 1) == -1)
	{
		close(id);
		return -1;
	}
	printf("done!\n");

	printf("Accepting1... \n");
	long_client = sizeof (client);
	printf("Accepting2... \n");
	printf("%d \n",id);
	son = accept(id, &client, &long_client);
	printf("Accepting3... \n");
	if (son == -1)
		return -1;
	printf("done!\n");

	printf("Reading... ");
	aux = read(son, data , 1);
	if(aux!=1)
		return -1;
	printf("\"%c\" ", data[0]);
	printf("done!\n");

	printf("Writing \"S\"... ");
	aux = send(son, "S", 1, MSG_NOSIGNAL);
	if(aux < 0)
		return -1;
	printf("done!\n");

	return 0;
}
