#include "circ_buffer.h"

bool is_buffer_full(circ_buffer **c1){
  if (((*c1)->tail + 1) % SIZE == (*c1)->head)
    return true;
  else
    return false;
}


bool is_buffer_empty(circ_buffer **c1){
  if ((*c1)->head == (*c1)->tail)
    return true;
  else
    return false;
}


int add_element(int in,circ_buffer **c1){

  int r = -1;
  if(is_buffer_full(c1)){
    printf("\n buffer full");
  }
  else{
    *((*c1)->buffer + (*c1)->tail) = in;
    (*c1)->tail = ((*c1)->tail + 1) % (SIZE);
    ++(*c1)->length;
    r = 0;
  }
  return r;
}


int remove_element(circ_buffer **c1){

  int r = -1;
  if(is_buffer_empty(c1)){
    printf("\nBuffer empty\n");
  }
  else{
    int data = *((*c1)->buffer + (*c1)->head);
    (*c1)->head = ((*c1)->head + 1) % SIZE;
    --(*c1)->length;
    r = 0;
  }
  // Moving head and tail to zero
  if((*c1)->tail == (SIZE-1) && (*c1)->head == (SIZE-1)){
    (*c1)->tail = ((*c1)->tail + 1) % (SIZE);
    (*c1)->head = ((*c1)->head + 1) % (SIZE);
  }
  return r;
}


void dump(circ_buffer *c1){
  int i;
  while(c1->head < c1->tail){
    printf("\nElement: %d\n", c1->buffer[c1->head]);
    ++c1->head;
  }

}


int init_buffer(circ_buffer **c1){

  int r = -1;
  *c1 = malloc(sizeof(circ_buffer));
  if(c1 == NULL){
    fprintf(stderr, "\nerror mallocing \n");
    exit(0);
  }
  (*c1)->buffer = malloc(SIZE*sizeof(int));
  if((*c1)->buffer == NULL){
    fprintf(stderr, "\nerror mallocing \n");
    exit(0);
  }
  (*c1)->length = 0;
  // (*c1)->head = &(*c1)->buffer[0];
  // (*c1)->tail = &(*c1)->buffer[0];
  (*c1)->head = 0;
  (*c1)->tail = 0;
  r = 0;
  return r;
}


void destroy(circ_buffer **c1){
  free((*c1)->buffer);
  free((*c1));
}
