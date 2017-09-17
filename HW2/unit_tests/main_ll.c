#include "db_ll.h"

int main(){
  // node_t *head = malloc(sizeof(node_t));
  // head->data = 4;
  // head->next = NULL;

  node_t *head = NULL;
  int ret;
  // ret = add_node(&head, 4);
  // printf("%d return add_node\n",ret );
  // add_node(&head, 5);
  // add_node(&head, 6);
  ret = add_node_index(&head, 7, 2);
  // printf("%d return add node index\n",ret );
  // display(head);
     // display_reverse(head);

  int where;
  ret = search(head,5,&where);
  printf("%d return search\n",ret );
  printf("\n where : %d", where);
  printf("\nnum of nodes: %d", size(head));
  display(head);
  ret = destroy(&head);
  printf("\n%d return destroy\n",ret );


}
