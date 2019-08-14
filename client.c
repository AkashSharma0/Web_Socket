// Client 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>

#define PORT 8000 
int main(int argc, char const *argv[]) 
{ 
	while(1)
	{
		int sock = 0, valread; 
		struct sockaddr_in serv_addr; 
		char *hello = "Hello from client"; 
		char *ip,buffer[2048];
		struct hostent *hp;
		char *host = "cpplusddns.com"; 

		// Convert IPv4 and IPv6 addresses from text to binary form
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{ 
		printf("\n Socket creation error \n"); 
		} 
		hp = gethostbyname(host);   
		serv_addr.sin_family = AF_INET; 
		serv_addr.sin_port = htons(PORT); 
		       
		// Convert IPv4 and IPv6 addresses from text to binary form
		//ip = inet_ntoa(*((struct in_addr *)hp->h_addr_list[0]));
		//serv_addr.sin_addr.s_addr = inet_addr(ip);


		ip = inet_ntoa(*((struct in_addr *)hp->h_addr_list[0]));
		serv_addr.sin_addr.s_addr = inet_addr(ip);
		printf("%s\n", ip ); 

		//if(inet_pton(AF_INET, "172.16.1.192", &serv_addr.sin_addr)<=0)  
		//{ 
		//printf("\nInvalid address/ Address not supported \n"); 
		//} 

		if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
		{ 
		printf("\nConnection Failed \n"); 
		} 
		else
		{	
		printf("4"); 
		memset(buffer,0,strlen(buffer));	       
		printf("Type Message\n"); 
		scanf("%s", buffer);
		printf("%d\n",strlen(buffer) );
		send(sock , buffer , strlen(buffer) , 0 );
		bzero((char *) &buffer, sizeof(buffer)); 
		valread = read( sock , buffer, 2048); 
		printf("%s\n",buffer ); 
		bzero((char *) &buffer, sizeof(buffer)); 
		}	
		//return 0;
		close(sock);   		
	}
} 
