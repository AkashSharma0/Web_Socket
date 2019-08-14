// server
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8000 
int main(int argc, char const *argv[]) 
{ 
	while(1)
	{
	    int server_fd, new_socket, valread; 
	    struct sockaddr_in address; 
	    int opt = 1; 
	    int addrlen = sizeof(address); 
	    char buffer[2048]; 
	    char *hello = "Hello from server"; 
	    char name[128] = "name";
            char date[128] = "date";
	    char time[128] = "time";
	    char *response1 = "camera";
	    char *response2 = "6.8.2019";
	    char *error = "Not Found";
	    int n=0;


	    memset(buffer,0,strlen(buffer));	       
	    // Creating socket file descriptor 
	    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	    { 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	    } 
	       
	    // Forcefully attaching socket to the port  
	    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	    } 
	    address.sin_family = AF_INET; 
	    address.sin_addr.s_addr = INADDR_ANY; 
	    address.sin_port = htons( PORT ); 
	       
	    // Forcefully attaching socket to the port  
	    if (bind(server_fd, (struct sockaddr *)&address,  
		                         sizeof(address))<0) 
	    { 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	    } 
	    if (listen(server_fd, 3) < 0) 
	    { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	    } 
	    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
		               (socklen_t*)&addrlen))<0) 
	    { 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	    } 
	    valread = read( new_socket , buffer, 2048); 
	    printf("%s\n",buffer );
	    if(!(strcmp(buffer,name)))
	    {
		n=1;
	    }
	    if(!(strcmp(buffer,date)))
	    {
		n=2;
	    }
   	    switch (n) 
   	    { 
	       	case 1: send(new_socket , response1 , strlen(response1) , 0 );
		break;  
    		case 2: send(new_socket , response2 , strlen(response2) , 0 );
		break;  
	 	default: send(new_socket , error , strlen(error) , 0 );
	    }
	    n=0; 
	    send(new_socket , hello , strlen(hello) , 0 ); 
	    printf("Hello message sent\n");
	    memset(buffer,0,strlen(buffer));
	    close(new_socket);
	    close(server_fd);	   
	    //return 0; 
	}
}
