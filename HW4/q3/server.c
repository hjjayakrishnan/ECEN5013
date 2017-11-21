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
​ ​* ​ ​@file ​ server.c
​ ​* ​ ​@brief ​ ​Server to be run on the BBG
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
#include <unistd.h>
#include <signal.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3001 /*port*/
#define LISTENQ 8 /*maximum number of client connections */
#define MAXBUFSIZE 100

int clients;

void int_handler(){
    close(clients);
    exit(0);
}


#define MAXBUFF 5

// "0" : Periodic mode
// "1" : Latch mode
int8_t setMode(char* mode){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/mode", "w+"))!=NULL){
        fwrite(mode, 1, sizeof(char), fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}

// "1" : Latch LED ON
// "0" : Latch LED OFF
// Ensure mode is set to Latch mode

int8_t setLED(char* state){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/ledState", "w+"))!=NULL){
        fwrite(state, 1, sizeof(char), fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}

// Set TIme period of LED flashing.
// Unit milliseconds
// Ensure mode is set to Periodic mode
int8_t setPeriod(char* period){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/period", "w+"))!=NULL){
        fwrite(period, 1, strlen(period)+1 , fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}


// Set duty cycle of LED flashing.
// (ON period)/period, input in percentage
// Ensure mode is set to Periodic mode
int8_t setDutycycle(char* dutycycle){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/dutycycle", "w+"))!=NULL){
        fwrite(dutycycle, 1, strlen(dutycycle)+1 , fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}

// "0" : Periodic mode
// "1" : Latch mode
int8_t readMode(char* mode){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/mode", "r"))!=NULL){
        fread(mode, 1, MAXBUFF*sizeof(char), fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}

// "1" :  LED ON
// "0" :  LED OFF

int8_t readLED(char* state){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/ledState", "r"))!=NULL){
        fread(state, 1, MAXBUFF*sizeof(char), fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}

// Read Time period of LED flashing.
// Unit milliseconds
// Ensure mode is set to Periodic mode
int8_t readPeriod(char* period){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/period", "r"))!=NULL){
        fread(period, 1, MAXBUFF*sizeof(char) , fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}


// Read duty cycle of LED flashing.
// (ON period)/period, input in percentage
// Ensure mode is set to Periodic mode
int8_t readDutycycle(char* dutycycle){

    FILE *fp;

    if((fp = fopen("/sys/ebb/gpio53/dutycycle", "r"))!=NULL){
        fread(dutycycle, 1, MAXBUFF*sizeof(char) , fp);
        fclose(fp);
    }else{
        perror("File Open Error:");
        return -1;
    }
    return 0;
}


int server_init(int *sock, int port){

  struct sockaddr_in server;
  bzero(&server,sizeof(struct sockaddr_in));               //zero the struct
	server.sin_family = AF_INET;                 //address family
	server.sin_port = htons(port);      //sets port to network byte order
	server.sin_addr.s_addr = htonl(INADDR_ANY); //sets remote IP address


  if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("unable to create socket");
	}

  if (bind(*sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		printf("******unable to bind socket********\n");
    exit(0);
	}

  if(listen (*sock, LISTENQ)<0){

    perror("listen error:");
  }
  printf("%s in port %d\n","Server running...waiting for connections.", port);
}


int parse_string(char *buffer, char **command, char **file){
    *file = strdup(buffer); //duplicate buffer
    *command = strsep(file, " ");
}




int main (int argc, char **argv)
{
    int sock;
    int port;
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    char buff_recv[25], *command, *file;

    char outmode[MAXBUFF];
    char outstate[MAXBUFF];
    char outperiod[MAXBUFF];
    char outdutycycle[MAXBUFF];
    memset(outmode, 0, MAXBUFF*sizeof(char));
    memset(outstate, 0, MAXBUFF*sizeof(char));
    memset(outperiod, 0, MAXBUFF*sizeof(char));
    memset(outdutycycle, 0, MAXBUFF*sizeof(char));



    if (argc !=2) {
        perror("Usage: <Port number>");
    exit(1);
    }
    port = atoi(argv[1]);
    server_init(&sock, port);
    clilen = sizeof(cliaddr);
    signal(SIGINT, int_handler);

    printf("waiting for a connection on port %d...\n",port);
    clients = accept(sock,(struct sockaddr *) &cliaddr, &clilen);
    printf("%s\n","Received request...");
    printf("\nWaiting for client...\n");

    while(1){

        recv(clients, buff_recv, MAXBUFSIZE,0);
        parse_string(buff_recv, &command, &file);
        printf("command: %s\n", command);

        if(!strcmp(command,"get")){

          if(!strcmp(file,"mode")){

            printf("get mode\n");
            readMode(outmode);
            send(clients, outmode, strlen(outmode)+1, 0);

          }else if(!strcmp(file,"ledstate")){

            printf("get ledstate\n");
             readLED(outstate);
            send(clients, outstate, strlen(outstate)+1, 0);

          }else if(!strcmp(file, "dutycycle")){

            printf("get dutycycle\n");
             readDutycycle(outdutycycle);
            send(clients, outdutycycle, strlen(outdutycycle)+1, 0);

          }else if(!strcmp(file, "period")){

            printf("get period\n");
             readPeriod(outperiod);
            send(clients, outperiod, strlen(outperiod)+1, 0);

          }else{

            printf("Invalid request. Try again. \n");
          }

        }
        else if(!strcmp(command, "put")){

          if(!strcmp(file,"mode")){

            printf("put mode\n");
            recv(clients, buff_recv, MAXBUFSIZE,0);
            printf("client said : %s\n", buff_recv);
            setMode(buff_recv);

          }else if(!strcmp(file,"ledstate")){

            printf("put ledstate\n");
            recv(clients, buff_recv, MAXBUFSIZE,0);
            printf("client said : %s\n", buff_recv);
            setLED(buff_recv);


          }else if(!strcmp(file, "dutycycle")){

            printf("put dutycycle\n");
            recv(clients, buff_recv, MAXBUFSIZE,0);
            printf("client said : %s\n", buff_recv);
            setDutycycle(buff_recv);

          }else if(!strcmp(file, "period")){

            printf("put period\n");
            recv(clients, buff_recv, MAXBUFSIZE,0);
            printf("client said : %s\n", buff_recv);
            setPeriod(buff_recv);

          }else{

            printf("Invalid request. Try again. \n");
          }

        }
        else{
          printf("Invalid command\n");
        }
    }


}
