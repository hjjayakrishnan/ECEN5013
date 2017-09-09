#ifndef _DBLL_H_
#define _DBLL_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef struct node{
  uint32_t data;
  struct node *next;
  struct node *prev;
}node_t;

void display(node_t *head);
void display_reverse(node_t *head);
int add_node(node_t **head, int data);
int add_node_index(node_t **head, int data, int index);
int search(node_t *head, int data, int *index);
int destroy(node_t **head);
int size(node_t *head);

#endif
