#ifndef _CIRCBUFF_H_
#define _CIRCBUFF_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#define SIZE 4

typedef struct buf{
  uint32_t *buffer;
  uint32_t length;
  uint32_t head;
  uint32_t tail;

}circ_buffer;

bool is_buffer_full(circ_buffer **c1);
bool is_buffer_empty(circ_buffer **c1);
int add_element(int in,circ_buffer **c1);
int remove_element(circ_buffer **c1);
void dump(circ_buffer *c1);
int init_buffer(circ_buffer **c1);
void destroy(circ_buffer **c1);

#endif
