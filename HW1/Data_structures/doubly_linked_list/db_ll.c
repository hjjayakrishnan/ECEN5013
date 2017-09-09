#include "db_ll.h"


void display(node_t *head){
  if(head){
    while(head->next != NULL){
      printf("data: %d\n",head->data );
      head = head->next;
    }
    printf("data: %d\n",head->data );
  }
  else
    printf("\n Linked List Empty");
}


void display_reverse(node_t *head){
  while(head->next != NULL){
    // printf("data: %d\n",head->data );
    head = head->next;
  }
  while(head->prev != NULL){
    printf("data: %d\n",head->data );
    head = head->prev;
  }

  printf("data: %d\n",head->data );
}


int add_node(node_t **head, int data){

  int r ;
  if((*head)==NULL){
    *head = malloc(sizeof(node_t));
    if(*head == NULL){
      r = -1;
      return r;
    }
    (*head)->data = data;
    (*head)->next = NULL;
    (*head)->prev = NULL;
    return 0;
  }
  node_t *temp;
  node_t *new_node = malloc(sizeof(node_t));
  if(new_node == NULL){
    r = -1;
    return r;
  }

  new_node->data = data;
  temp = (*head);
  while((*head)->next !=NULL ){
    *head = (*head)->next;
  }
  (*head)->next = new_node;
  new_node->prev = (*head);
  (*head) = temp;
  return r;
}


int add_node_index(node_t **head, int data, int index){

  int node_count = 0;
  int r = 0;
  node_t *temp;
  node_t *temp_next;
  node_t *new_node = malloc(sizeof(node_t));
  if(new_node == NULL){
    r = -1;
    return r;
  }
  new_node->data = data;
  temp = (*head);

  if((*head)==NULL){
    *head = malloc(sizeof(node_t));
    if(*head == NULL){
      r = -1;
      return r;
    }
    (*head)->data = data;
    (*head)->next = NULL;
    return r;
  }

  if (index == 0){
    new_node->next = *head;
    *head = new_node;
    return r;
  }

  while(node_count < (index) ){
    if(node_count == (index-1)){
      temp_next = (*head)->next;
      break;
    }

    *head = (*head)->next;
    ++node_count;
   }
  (*head)->next = new_node;
  new_node->prev = (*head);
  new_node->next = temp_next;
  temp_next->prev = new_node;
  (*head) = temp;
  return r;
}


int search(node_t *head, int data, int *index){
  int node_count = 0;
  int r = -1;
  while(head->next!=NULL){
    if(head->data == data){
      *index = node_count;
      r = 0;
      return r;
    }
    head = head->next;
    ++node_count;
  }
  if(head->data == data){
    *index = node_count;
    r = 0;
    return r;
  }
  return r;
}


int destroy(node_t **head){

  int r;
  node_t * temp;
  if((*head) == NULL){
    r = -1;
    return r;
  }
  while((*head)->next != NULL){
    temp = (*head)->next;
    free(*head);
    (*head) = temp;
  }
  free(*head);
  *head = NULL;
  r = 0;
  return r;
}


int size(node_t *head){
  int node_count = 0;
  while(head->next !=NULL){
    ++node_count;
    head = head->next;
  }
  return (node_count+1);
}
