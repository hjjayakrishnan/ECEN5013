#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

int main(){

  int *buffer;
  int len = 15;
  buffer = malloc(len*sizeof(int));

  int i, j, temp;
  srand (time(NULL));
  for(i=0;i<len;i++){
    buffer[i] = rand()%100;
  }

  for(i=0;i<len;i++){
    printf("%d : %d\n",i,buffer[i]);
  }



  for(i=0;i<len;i++){
    for(j=0;j<len;j++){
      if (*(buffer+i)< *(buffer+j)){
        temp = *(buffer+i);
        *(buffer+i) = *(buffer+j);
        *(buffer+j) = temp;
      }
    }
  }

  printf("\n after sorting \n");
  for(i=0;i<len;i++){
    printf("%d : %d\n",i,buffer[i]);
  }
}
