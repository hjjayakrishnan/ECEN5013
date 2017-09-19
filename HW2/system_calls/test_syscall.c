#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>


int main(){

  int32_t *buffer;
  int32_t *out_buffer;
  int32_t len = 256;
  buffer = malloc(len*sizeof(long));
  out_buffer = malloc(len*sizeof(long));

  int32_t i, j, temp;
  srand (time(NULL));
  for(i=0;i<len;i++){
    buffer[i] = rand()%100;
  }

  for(i=0;i<len;i++){
    printf("%ld : %ld\n",(long)i,(long)buffer[i]);
  }
  int ret = syscall(333, buffer,out_buffer, len);
  printf("\n%d",ret);
  // perror(ret);
  printf("\n after sorting \n");
  for(i=0;i<len;i++){
    printf("%ld : %ld\n",(long)i,(long)out_buffer[i]);
  }
}
