/*****************************************************************************
​ ​* ​ ​Copyright ​ ​(C) ​ ​2017 ​ ​by ​ Jayakrishnan HJ
​ ​*
​ ​* ​ ​Redistribution, ​ ​modification ​ ​or ​ ​use ​ ​of ​ ​this ​ ​software ​ ​in ​ ​source ​ ​or ​ ​binary
​ ​* ​ ​forms ​ ​is ​ ​permitted ​ ​as ​ ​long ​ ​as ​ ​the ​ ​files ​ ​maintain ​ ​this ​ ​copyright. ​ ​Users ​ ​are
​ ​* ​ ​permitted ​ ​to ​ ​modify ​ ​this ​ ​and ​ ​use ​ ​it ​ ​to ​ ​learn ​ ​about ​ ​the ​ ​field ​ ​of ​ ​embedded
​ ​* ​ ​software. ​ ​Jayakrishnan  HJ ​ ​and ​ ​the ​ ​University ​ ​of ​ ​Colorado ​ ​are ​ ​not ​ ​liable ​ ​for
​ ​* ​ ​any ​ ​misuse ​ ​of ​ ​this ​ ​material.
​ ​*
*****************************************************************************/
/**
​ ​* ​ ​@file ​ client.c
​ ​* ​ ​@brief ​ ​Remote client to remotely control BBG LED through sockets
​ ​*
​ ​* ​ ​This  ​file ​ ​provides ​ ​an ​ ​abstraction ​ ​of ​ ​reading ​ ​and
​ ​* ​ ​writing ​ ​to ​ various  states  of  an  LED.
​ ​*
​ ​* ​ ​@author ​ Jayakrishnan HJ
​ ​* ​ ​@date ​ ​November ​ 20 ​ ​2017
​ ​* ​ ​@version ​ ​1.0
​ ​*
​ ​*/


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3001 /*port*/
#define MAXBUFSIZE 25

int client_init(int *sock, struct sockaddr_in **remote, char *server_ip, int port){

printf("port:%d \n",port);
  *remote = malloc(sizeof(struct sockaddr_in));

  if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("unable to create socket");
	}

  bzero(*remote,sizeof(struct sockaddr_in));               //zero the struct
	(*remote)->sin_family = AF_INET;                 //address family
	(*remote)->sin_port = htons(port);      //sets port to network byte order
	(*remote)->sin_addr.s_addr = inet_addr(server_ip); //sets remote IP address

  //Connection of the client to the socket
 if (connect(*sock, (struct sockaddr *) *remote, sizeof(struct sockaddr_in))<0) {
  perror("Problem in connecting to the server");
  return -1;
 }
 return 0;
}


int parse_string(char *buffer, char **command, char **file){
  *file = strdup(buffer); //duplicate buffer
  *command = strsep(file, " ");
}



int main(int argc, char **argv){

  int sock;
  int port;
  char buff_recv[MAXBUFSIZE], *command, *file;
  struct sockaddr_in *remote;

  if (argc !=3) {
  perror("Usage: client <SERVER IP> <PORT>");
  exit(1);
 }


 port = atoi(argv[2]);
 client_init(&sock, &remote,  argv[1], port);

printf("\n\n******** Beaglebone remote LED control ********\n\n\n");
printf("OPTIONS:\n\n");
printf("Item list :");
printf("mode, ledstate, dutycycle, period\n\n");
printf("1. put <item>\n\n");
printf("2. get <item>\n\n");
  /*   State Machine  */
  while(1){

    printf("\nEnter command: ");
    scanf(" %[^\n]s", buff_recv);

    send(sock, buff_recv, strlen(buff_recv)+1, 0);

    parse_string(buff_recv, &command, &file);

    if(!strcmp(command,"get")){

      recv(sock, buff_recv, MAXBUFSIZE,0);
      printf("%s: %s\n\n", file, buff_recv);

    }
    else if(!strcmp(command, "put")){

      if(!strcmp(file,"mode")){

        printf("put mode");
        printf("\nEnter value (0 or 1): ");
        scanf(" %[^\n]s", buff_recv);
        send(sock, buff_recv, strlen(buff_recv)+1, 0);

      }else if(!strcmp(file,"ledstate")){

        printf("put ledstate");
        printf("\nEnter value (0 or 1): ");
        scanf(" %[^\n]s", buff_recv);
        send(sock, buff_recv, strlen(buff_recv)+1, 0);

      }else if(!strcmp(file, "dutycycle")){

        printf("put dutycycle");
        printf("\nEnter value (between 10 and 80): ");
        scanf(" %[^\n]s", buff_recv);
        send(sock, buff_recv, strlen(buff_recv)+1, 0);

      }else if(!strcmp(file, "period (between 100 and 10000)")){

        printf("put period (between 10 and 10000)");
        printf("\nEnter value: ");
        scanf(" %[^\n]s", buff_recv);
        send(sock, buff_recv, strlen(buff_recv)+1, 0);

      }else{

        printf("Invalid request. Try again. \n");
      }

    }
    else{
      printf("Invalid command\n");
    }

  }

}
