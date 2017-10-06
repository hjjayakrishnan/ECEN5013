#include <pthread.h>
#include <time.h>

clock_t start,stop;

void *Printthread(void *threadid){
  stop = clock();
  printf("Pthread creation time: %f s\n", ((double)(stop - start))/CLOCKS_PER_SEC);
}

int main(){

  pthread_t thread1;
  int rc;
  start = clock();
  rc = pthread_create(&thread1, NULL, Printthread, NULL);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
 }
 pthread_exit(NULL);
}
