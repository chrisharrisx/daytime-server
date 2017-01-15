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
#define DAYTIME_PORT 3333
 
int main(int argc, char **argv) {
  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];
  time_t ticks;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(DAYTIME_PORT); /* daytime server */
  bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);
 
  for ( ; ; ) {
    connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
    ticks = time(NULL);
   
    struct addrinfo hints, *info, *p;
    int gai_result;

    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    if ((gai_result = getaddrinfo(hostname, "http", &hints, &info)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
      exit(1);
    }

    for (p = info; p != NULL; p = p->ai_next) {
      printf("Server Name: %s\nIP Address: %s\n", p->ai_canonname, p->ai_address->sa_data);
    }
   
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    
    write(connfd, buff, strlen(buff));
    printf("Sending response: %s", buff);
    close(connfd);
  }
 
  freeaddrinfo(info);
}
