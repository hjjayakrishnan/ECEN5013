#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <semaphore.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUM_THREADS 2
#define BUFFSIZE 100
#define SNDRCV_MQ "/send_receive_mq"
#define MAX_MSG_SIZE 128
#define ERROR (-1)

// Message queue atttributes

struct mq_attr mq_attr;

typedef struct{
  int threadIdx;
}threadParams_t;

pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];

//Scheduler declarations
pthread_attr_t rt_sched_attr[NUM_THREADS];
int rt_max_prio, rt_min_prio;
struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
pthread_attr_t main_attr;
pid_t mainpid;
//Semaphores
sem_t readSem, reportSem;
char file[] = "enthero";
int length;


/* analyze the string */
int Analyze(char *buffer, char **stat){
  int i;
  int index;
  for(i = 0; i< strlen(buffer); i++){
    index = buffer[i];
    ++*(*stat+index);
    // printf("\n i: %d", *stat[i]);
  }
}

/* write to file */
int writeFile(char *fileName){

  FILE *fpw;
  char *buffer;
  int nbytes;
  buffer = malloc(BUFFSIZE*sizeof(char));
  fpw = fopen(fileName, "w");
  printf("\nWhat do you want: ");
  fgets(buffer, BUFFSIZE, stdin);
  length = strlen(buffer)+1;
  nbytes = fwrite(buffer, 1, length, fpw);
  free(buffer);
  fclose(fpw);
  kill(mainpid, SIGUSR1);
  // sem_post(&readSem);
}

/* read thread */
void *readFile(void *threadp){
  sem_wait(&readSem);
  int i;
  //printf("readthread\n" );
  mqd_t mymq;
  char buff[MAX_MSG_SIZE];
  int prio;
  int nbytes;
  static char *statistics;
  FILE *fpr;
  statistics = (char*)calloc(MAX_MSG_SIZE,sizeof(char));

  fpr=fopen(file,"r");
  if(fpr<0){
    perror("fopen:");
  }

  nbytes = fread(buff, 1, length, fpr );
  if(nbytes<0){
    perror("fread:");
  }
  fclose(fpr);
  Analyze(buff, &statistics);

  //Open message queue
  mymq = mq_open(SNDRCV_MQ, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);

  if(mymq < 0)
  {
    perror("sender mq_open");
    exit(-1);
  }
  else
  {
    printf("sender opened mq\n");
  }

  /* send message with priority=30 */
  if((nbytes = mq_send(mymq, statistics, MAX_MSG_SIZE*sizeof(char), 30)) == ERROR)
  {
    perror("mq_send");
  }
  else
  {
    printf("send: message successfully sent\n");
  }
  kill(mainpid, SIGUSR2);
  // sem_post(&reportSem);
}

/* report thread */
void *reportThread(void *threadp){
  sem_wait(&reportSem);
  //printf("reportthread\n" );
  mqd_t mymq;
  char buff[MAX_MSG_SIZE];
  int prio;
  int nbytes;
  int i;
  int char_sum;
// Open message queue
  mymq = mq_open(SNDRCV_MQ, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);

  if(mymq == (mqd_t)ERROR)
  {
    perror("receiver mq_open");
    exit(-1);
  }

  /* read oldest, highest priority msg from the message queue */
  if((nbytes = mq_receive(mymq, buff, MAX_MSG_SIZE, &prio)) == ERROR)
  {
    perror("mq_receive");
  }
  else
  {
    // buff[nbytes] = '\0';
    // printf("receive: msg %s received with priority = %d, length = %d\n",
    //        buff, prio, nbytes);
  }

  printf("************************************statistics************************************\n");
  printf("No of words: %d\n",buff[32] +1 );
  printf("Duplicate characters: ");
  for(i=0;i<MAX_MSG_SIZE;i++){
    if (buff[i]>1 && i!=32){
      printf("%c, ", i);
    }
    if(i!=32)
      char_sum+= buff[i];
  }
  printf("\nNo. of characters: %d\n", char_sum-1);
}


void print_scheduler(void)
{
 int schedType;

 schedType = sched_getscheduler(getpid());

 switch(schedType)
 {
   case SCHED_FIFO:
         printf("Pthread Policy is SCHED_FIFO\n");
         break;
   case SCHED_OTHER:
         printf("Pthread Policy is SCHED_OTHER\n");
     break;
   case SCHED_RR:
         printf("Pthread Policy is SCHED_OTHER\n");
         break;
   default:
     printf("Pthread Policy is UNKNOWN\n");
 }
}
static void handler1(int signum){
  printf("Releasing semaphore for reading...\n");
  sem_post(&readSem);
}


static void handler2(int signum){
  printf("Releasing sempahore for reporting...\n");
  sem_post(&reportSem);
}


int main (int argc, char *argv[])
{
  int rc;
  int i;

  /* setup common message q attributes */
  mq_attr.mq_maxmsg = 10;
  mq_attr.mq_msgsize = MAX_MSG_SIZE;
  mq_attr.mq_flags = 0;

  /* Signal handler */
  struct sigaction sa;
  sa.sa_handler = handler1;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
  struct sigaction sa2;
  sa2.sa_handler = handler2;
  sigemptyset(&sa2.sa_mask);
  sa2.sa_flags = SA_RESTART;
  if (sigaction(SIGUSR2, &sa2, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }


  /* initialize semaphore */
  sem_init(&readSem,0,0);
  sem_init(&reportSem,0,0);

  mainpid=getpid();

  /* scheduler */
  print_scheduler();
  rc=sched_getparam(mainpid, &main_param);
  if (rc)
   {
     printf("ERROR; sched_setscheduler rc is %d\n", rc);
     perror(NULL);
     exit(-1);
   }
   //Obtain the priorities of the scheduler
  rt_max_prio = sched_get_priority_max(SCHED_FIFO);
  rt_min_prio = sched_get_priority_min(SCHED_FIFO);

  main_param.sched_priority=rt_max_prio;
  rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
  if(rc < 0) perror("main_param");
  print_scheduler();

  for(i=0; i < NUM_THREADS; i++)
  {
    rc=pthread_attr_init(&rt_sched_attr[i]);
    rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
    rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
    rt_param[i].sched_priority=rt_max_prio-i-1;
    pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

    threadParams[i].threadIdx=i;
  }
/*********************************************************************************/
  // initializeClient();
  // signal(SIGINT, int_handler);
/*********************************************************************************/

	//Thread creation
  pthread_create(&threads[0],   // pointer to thread descriptor
                 &rt_sched_attr[0],     // use default attributes
	                readFile, // thread function entry
                 (void *)&(threadParams[0]) // parameters to pass in		//Cant pass nothing so just pass a number
		);

  pthread_create(&threads[1],   // pointer to thread descriptor
		             &rt_sched_attr[1],     // use default attributes
		             reportThread, // thread function entry point
	               (void *)&(threadParams[1]) // parameters to pass in		//Cant pass nothing so just pass a number
		);
/*********************************************************************************/

  writeFile(file);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

/*********************************************************************************/
}
