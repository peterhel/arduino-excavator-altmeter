#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <cctype>
#define PORT 8080 

static const char *hello = "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";

static const char* B64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int B64index[256] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62, 63, 62, 62, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63,
    0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

const std::string b64encode(const void* data, const size_t &len)
{
    std::string result((len + 2) / 3 * 4, '=');
    char *p = (char*) data, *str = &result[0];
    size_t j = 0, pad = len % 3;
    const size_t last = len - pad;

    for (size_t i = 0; i < last; i += 3)
    {
        int n = int(p[i]) << 16 | int(p[i + 1]) << 8 | p[i + 2];
        str[j++] = B64chars[n >> 18];
        str[j++] = B64chars[n >> 12 & 0x3F];
        str[j++] = B64chars[n >> 6 & 0x3F];
        str[j++] = B64chars[n & 0x3F];
    }
    if (pad)  /// set padding
    {
        int n = --pad ? int(p[last]) << 8 | p[last + 1] : p[last];
        str[j++] = B64chars[pad ? n >> 10 & 0x3F : n >> 2];
        str[j++] = B64chars[pad ? n >> 4 & 0x03F : n << 4 & 0x3F];
        str[j++] = pad ? B64chars[n << 2 & 0x3F] : '=';
    }
    return result;
}

const std::string b64decode(const void* data, const size_t &len)
{
    if (len == 0) return "";

    unsigned char *p = (unsigned char*) data;
    size_t j = 0,
        pad1 = len % 4 || p[len - 1] == '=',
        pad2 = pad1 && (len % 4 > 2 || p[len - 2] != '=');
    const size_t last = (len - pad1) / 4 << 2;
    std::string result(last / 4 * 3 + pad1 + pad2, '\0');
    unsigned char *str = (unsigned char*) &result[0];

    for (size_t i = 0; i < last; i += 4)
    {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;
    }
    if (pad1)
    {
        int n = B64index[p[last]] << 18 | B64index[p[last + 1]] << 12;
        str[j++] = n >> 16;
        if (pad2)
        {
            n |= B64index[p[last + 2]] << 6;
            str[j++] = n >> 8 & 0xFF;
        }
    }
    return result;
}

std::string b64encode(const std::string& str)
{
    return b64encode(str.c_str(), str.size());
}

std::string b64decode(const std::string& str64)
{
    return b64decode(str64.c_str(), str64.size());
}

int main() {
    std::cout << "Hello World\n";

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
       
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
    std::string hello2 = b64decode(hello, strlen(hello));
    const char * hello3 = hello2.c_str();
    printf("Length of response is: %u\n", hello2.length());
    send(new_socket , hello2.c_str() , hello2.length() , 0 ); 
    printf("Hello message sent\n"); 
    return 0; 
}
