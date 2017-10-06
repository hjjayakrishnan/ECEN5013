#include <stdio.h>
#include <sys/types.h>
#include <time.h>

clock_t start,stop;

int main(){

  int rc;
  double start, stop;
  pid_t my_pid, parent_pid, child_pid;
  my_pid = getpid();
  parent_pid = my_pid;
  printf("I'm the parent: %d, forking child hello_world \n", parent_pid);

  start = clock();
  if((rc = fork())==0){ // Forks the parent

    execv("hello_world", NULL); // executes hello_world

  }
  else if(rc < 0){

    printf("\n Fork Failed \n");
  }

  wait(); // The parent meanwhile waits for child to finish
  stop = clock();
  printf("\nTime delay for fork-exec : %f s", ((double)(stop - start))/CLOCKS_PER_SEC);
  my_pid = getpid();
  printf("\nParent continues..., pid : %d \n", my_pid);
  return 0;
}
