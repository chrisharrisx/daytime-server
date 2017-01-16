#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 4096 /* max text line length */
#define LISTENQ 1024 /* 2nd argument to listen() */
 
int main(int argc, char **argv) {
  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];
  time_t ticks;

  if (argc < 2) {
    printf("Usage: %s <port number>\n", argv[0]);
    exit(1);
  }

  for (int i = 0; argv[1][i] != '\0'; i++) {
    if (!isdigit(argv[1][i])) {
      puts("Port number must be an integer");
    }
  }
  int port_num = atoi(argv[1]);

  if (port_num < 1024) {
    puts("Port number must be greater than 1024");
    exit(1);
  }

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port_num); /* daytime server */
  
  bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  
  listen(listenfd, LISTENQ);
 
  for ( ; ; ) {
    connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
    ticks = time(NULL);
   
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    
    write(connfd, buff, strlen(buff));
    printf("Sending response: %s", buff);
    close(connfd);
  }
}
