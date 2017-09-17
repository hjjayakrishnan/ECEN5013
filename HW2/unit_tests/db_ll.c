#include "db_ll.h"


int display(node_t *head){
  enum dbll_status status;
  if(head){
    while(head->next != NULL){
      printf("data: %d\n",head->data );
      head = head->next;
    }
    printf("data: %d\n",head->data );
  }
  else{
    printf("\n Linked List Empty");
    return EMPTY;
  }
  return SUCCESS;
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

  enum dbll_status status;
  int r ;
  if((*head)==NULL){
    *head = malloc(sizeof(node_t));
    if(*head == NULL){
      return FAILURE;
    }
    (*head)->data = data;
    (*head)->next = NULL;
    (*head)->prev = NULL;
    return SUCCESS;
  }
  node_t *temp;
  node_t *new_node = malloc(sizeof(node_t));
  if(new_node == NULL){
    r = -1;
    return FAILURE;
  }

  new_node->data = data;
  temp = (*head);
  while((*head)->next !=NULL ){
    *head = (*head)->next;
  }
  (*head)->next = new_node;
  new_node->prev = (*head);
  new_node->next = NULL;
  (*head) = temp;
  return SUCCESS;
}


int add_node_index(node_t **head, int data, int index){

  int node_count = 0;
  enum dbll_status status;
  int r;
  node_t *temp;
  node_t *temp_next;
  node_t *new_node = malloc(sizeof(node_t));
  if(new_node == NULL){
    return FAILURE;
  }
  new_node->data = data;
  temp = (*head);

  if((*head)==NULL){
    *head = malloc(sizeof(node_t));
    if(*head == NULL){
      r = -1;
      return FAILURE;
    }
    (*head)->data = data;
    (*head)->next = NULL;
    return SUCCESS;
  }

  if (index == 0){
    new_node->next = *head;
    *head = new_node;
    return SUCCESS;
  }

  while(node_count < (index) ){
    if(node_count == (index-1)){
      temp_next = (*head)->next;
      if((*head)->next == NULL){
        (*head)->next = new_node;
        new_node->prev = (*head);
        (*head) = temp;
        return SUCCESS;
      }
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
  return SUCCESS;
}


int search(node_t *head, int data, int *index){
  int node_count = 0;
  int r = -1;
  enum dbll_status status;

  if(head==NULL){
    *index = NO_DATA;
    return EMPTY;
  }

  while(head->next!=NULL){
    if(head->data == data){
      *index = node_count;
      r = 0;
      return SUCCESS;
    }
    head = head->next;
    ++node_count;
  }
  if(head->data == data){
    *index = node_count;
    r = 0;
    return SUCCESS;
  }
  *index = NO_DATA; // Data not found
  return FAILURE;
}


int destroy(node_t **head){

  int r;
  node_t * temp;
  enum dbll_status status;
  if((*head) == NULL){
    r = -1;
    return EMPTY;
  }
  while((*head)->next != NULL){
    temp = (*head)->next;
    free(*head);
    (*head) = temp;
  }
  free(*head);
  *head = NULL;
  r = 0;
  return SUCCESS;
}


int size(node_t *head){
  int node_count = 0;

  if(head==NULL){
    return EMPTY;
  }

  while(head->next !=NULL){
    ++node_count;
    head = head->next;
  }
  return (node_count+1);
}
