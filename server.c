#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void doprocessing (int sock) {
   int n;
   char buffer[256];
   bzero(buffer,256);
   n = read(sock,buffer,255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
}

int main( int argc, char *argv[] ) {
   int sockfd;
   int newsockfd;
   int portno = 1500;
   int clilen;
   char buffer[256];
   struct sockaddr_in serv_addr;
   struct sockaddr_in cli_addr;
   int n;
   int pid;
   
   /* 
    * Создаю сокет типа IPv4(AF_INET),
    * SOCK_STREAM - флаг потоковой передачи данных.
    */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("ERROR while opening socket");
      exit(1);
   }
   
   /* 
    * Инициализирую структуру сокета. 
    */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* 
    * Соидиняю сокет со структутор с описанием
    */
   if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /*
    * Сервер начинает слушать сокет sockfd.
    * максимальное количество конектов = 5.
    */
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
      pid = fork();
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         // клиентский процесс
         close(sockfd);
         doprocessing(newsockfd);
         exit(0);
      }
      else {
         close(newsockfd);
      }
      
   } 
}
