/* ET - External Tracer
 * Copyright (C) 2019 Erich Studer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/un.h>

#include "network.h"

#define PORT 65432

int comSocket;

int networkInit(void){
	struct sockaddr_in addr;
	int socketId;
	
	memset(&addr,0,sizeof(addr));
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//create socket
	socketId = socket(AF_INET, SOCK_STREAM, 0);
	if (socketId == -1){
		return EXIT_FAILURE;
	}
	
	//configure socket
	int idReuse=1;
	if(setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &idReuse, sizeof(idReuse)) == -1){
	   return EXIT_FAILURE;
	}
	
	//binding
	if(bind(socketId, (struct sockaddr *)&addr, sizeof(addr)) == -1){
		close (socketId);
		return EXIT_FAILURE;
	}
	
	//mark socket as listening
	if (listen(socketId , 1) == -1){
		close(socketId);
		return EXIT_FAILURE;
	}

	//accepting
	struct sockaddr client;//never used
	socklen_t long_client = sizeof(client);
	comSocket = accept(socketId, &client, &long_client);
	if (comSocket == -1){
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

int networkSend(const void *buf, size_t len){
	int numCharSent = send(comSocket, buf, len, MSG_NOSIGNAL);
	if(numCharSent < 0){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/* int networkRead(int comSocket, void *buf, size_t count){
	numByteRead = read(son, data , 1);
	if(numByteRead != 1){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
} */

//networkClose
