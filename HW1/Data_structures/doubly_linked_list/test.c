#include "db_ll.h"

int main(){
  // node_t *head = malloc(sizeof(node_t));
  // head->data = 4;
  // head->next = NULL;

  node_t *head = NULL;
  add_node(&head, 4);
  add_node(&head, 5);
  add_node(&head, 6);
  add_node_index(&head, 7, 2);
  display(head);
  // display_reverse(head);
  // node_t *n1 = malloc(sizeof(node_t));
  int where;
  search(head,4,&where);
  printf("\n where : %d", where);
  printf("\nnum of nodes: %d", size(head));
  destroy(&head);
  display(head);

}
