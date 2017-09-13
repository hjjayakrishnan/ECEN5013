
#include "circ_buffer.h"

int main(){


  circ_buffer *c1;
  init_buffer(&c1);
  int in;
  add_element(5, &c1);
  add_element(6, &c1);
  printf("\n %d tail \n",c1->tail);
  printf("\n %d head\n ",c1->head);
  remove_element(&c1);
  printf("\n %d tail \n",c1->tail);
  printf("\n %d head\n ",c1->head);
  add_element(7, &c1);

  dump(c1);
  destroy(&c1);
}
