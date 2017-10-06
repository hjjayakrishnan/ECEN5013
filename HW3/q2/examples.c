#define _GNU_SOURCE

#include <pthread.h>
#include <sched.h>
#include <stdio.h>

#define NUM_THREADS 3
#define MUTEX_LOCK // comment for MUTEX_TRYLOCK

typedef struct{
  int threadIdx;
}threadParams_t;

pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];
//Scheduler declarations
pthread_attr_t rt_sched_attr[NUM_THREADS], attr;
int rt_max_prio, rt_min_prio;
struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
pthread_attr_t main_attr;
pid_t mainpid;
pthread_t threadid;
//mutex
pthread_mutex_t mutexsem;
//condition var
pthread_cond_t pcond;
//global shared memory
int globalvar = 0;

/* thread 1                  */
void *threadex1(void *threadp){

  printf("\nthread 1\n");
  threadid = pthread_self();

  #ifdef MUTEX_LOCK
    pthread_mutex_lock(&mutexsem);

    while(globalvar!= 1)
      pthread_cond_wait(&pcond, &mutexsem); // We wait until globalvar is 1
    ++globalvar;
    pthread_mutex_unlock(&mutexsem);

  #else
    pthread_mutex_trylock(&mutexsem);
    ++globalvar;
    pthread_mutex_unlock(&mutexsem);

  #endif

  printf("\nthread 1 id is : %u\n",threadid );
  printf("\nshared memory value (globalvar) : %d\n", globalvar);
  pthread_exit(NULL); //exits the current calling thread
}

/* thread 2                  */
void *threadex2(void *threadp){

  int rc;
  size_t stack_size;
  printf("\nthread 2\n");
  rc = pthread_getattr_np(pthread_self(), &attr);
  pthread_attr_getstacksize(&attr, &stack_size);
  printf("\nstack size: %ld\n", stack_size);

  pthread_exit(NULL); // exits the current calling thread
}

/* thread 3                  */
void *threadex3(void *threadp){
  printf("\nthread 3\n");
  pthread_mutex_lock(&mutexsem);
  ++globalvar;
  pthread_cond_signal(&pcond); // Signal as now globalvar is 1
  pthread_mutex_unlock(&mutexsem);
}


int main(){

  int rc;
  int i;

  mainpid=getpid();

  pthread_mutex_init(&mutexsem, NULL);

  //Initialize condition variable to its default config
  pthread_cond_init(&pcond, NULL);
  /* scheduler */

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
                  threadex1, // thread function entry
                 (void *)&(threadParams[0]) // parameters to pass in		//Cant pass nothing so just pass a number
    );

  pthread_create(&threads[1],   // pointer to thread descriptor
                 &rt_sched_attr[1],     // use default attributes
                 threadex2, // thread function entry point
                 (void *)&(threadParams[1]) // parameters to pass in		//Cant pass nothing so just pass a number
    );

  pthread_create(&threads[2],   // pointer to thread descriptor
                 &rt_sched_attr[2],     // use default attributes
                 threadex3, // thread function entry point
                 (void *)&(threadParams[2]) // parameters to pass in		//Cant pass nothing so just pass a number
    );
/*********************************************************************************/


  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_mutex_destroy(&mutexsem);
  pthread_cond_destroy(&pcond);

/*********************************************************************************/
}
