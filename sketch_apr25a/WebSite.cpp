#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "base64.h"
#include <cctype>
#define PORT 8080 
int main() {
    std::cout << "Hello World\n";

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "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";
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
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
 //   valread = read( new_socket , buffer, 1024); 
 //   printf("%s\n",buffer ); 
    char *hello2 = base64_decode(hello);
    send(new_socket , hello2 , strlen(hello2) , 0 ); 
    printf("Hello message sent\n"); 
    return 0; 
}
