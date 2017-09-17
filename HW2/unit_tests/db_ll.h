/*****************************************************************************
​ ​* ​ ​Copyright ​ ​(C) ​ ​2017 ​ ​by ​ Jayakrishnan HJ
​ ​*
​ ​* ​ ​Redistribution, ​ ​modification ​ ​or ​ ​use ​ ​of ​ ​this ​ ​software ​ ​in ​ ​source ​ ​or ​ ​binary
​ ​* ​ ​forms ​ ​is ​ ​permitted ​ ​as ​ ​long ​ ​as ​ ​the ​ ​files ​ ​maintain ​ ​this ​ ​copyright. ​ ​Users ​ ​are
​ ​* ​ ​permitted ​ ​to ​ ​modify ​ ​this ​ ​and ​ ​use ​ ​it ​ ​to ​ ​learn ​ ​about ​ ​the ​ ​field ​ ​of ​ ​embedded
​ ​* ​ ​software. ​ ​Alex ​ ​Fosdick ​ ​and ​ ​the ​ ​University ​ ​of ​ ​Colorado ​ ​are ​ ​not ​ ​liable ​ ​for
​ ​* ​ ​any ​ ​misuse ​ ​of ​ ​this ​ ​material.
​ ​*
*****************************************************************************/
/**
​ ​* ​ ​@file ​ db_ll.h
​ ​* ​ ​@brief ​ ​API for a doubly linked list data structure
​ ​*
​ ​* ​ ​This ​ ​header ​ ​file ​ ​provides ​ ​an ​ ​abstraction ​ ​of ​ ​reading ​ ​and
​ ​* ​ ​writing ​ ​to ​ ​a doubley linked list ​ ​via ​ ​function ​ ​calls.
​ ​*
​ ​* ​ ​@author ​ Jayakrishnan HJ
​ ​* ​ ​@date ​ ​September ​ 8 ​ ​2017
​ ​* ​ ​@version ​ ​1.0
​ ​*
​ ​*/

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

enum dbll_status{SUCCESS = 0, FAILURE = -1, NO_DATA = -2, EMPTY = -4};

/**
​ ​* ​ ​@display  elements
​ ​*
​ ​* ​ Display  elements  of  the  doubly  linkedlist
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ head ​ Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​ ​
​ ​*
​ ​* ​ ​@return ​ void.
​ ​*/
int display(node_t *head);

/**
​ ​* ​ ​@brief ​ display  reverse  of a  double  linked  list
​ ​*
​ ​* ​ Useful  to  debug
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ head ​ Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ status.
​ ​*/
void display_reverse(node_t *head);

/**
​ ​* ​ ​@brief ​ add  element  to  doubly  linked  list  node
​ ​*
​ ​* ​ add  element  to  doubly  linked  list  node
​ ​* ​ ​at  the  end
​ ​*
​ ​* ​ ​@param ​ head ​ ​Double  Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​ ​@param ​ ​data ​ ​Add  element  to  the   ​doubly  linked  list
​ ​*
​ ​* ​ ​@return ​ ​​status.
​ ​*/
int add_node(node_t **head, int data);

/**
​ ​* ​ ​@brief ​ add  element  to  doubly  linked  list  node
​ ​*
​ ​* ​ add  element  to  doubly  linked  list  node
​ ​* ​ ​at  specified  index
​ ​*
​ ​* ​ ​@param ​ head ​ ​Double  Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​ ​@param ​ ​data ​ ​Add  element  to  the  ​doubly  linked  list
​ ​*  ​@param  index   where  data  is  to  be  added
​ ​* ​ ​@return ​ ​​status.
​ ​*/
int add_node_index(node_t **head, int data, int index);

/**
​ ​* ​ ​@brief ​ search  element  in  the  double  linked  list
​ ​*
​ ​* ​ search  element  in  the  double  linked  list
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ head ​ ​Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​ ​@param ​ ​in ​ ​Add  element  to  the  circular  buffer
​ ​*  ​@param  index   Pointer  index  of  the  data  is stored
​ ​* ​ ​@return ​ ​​status.
​ ​*/
int search(node_t *head, int data, int *index);

/**
​ ​* ​ ​@brief ​ destroys  the  doubly  lnked  list
​ ​*
​ ​* ​ destroys  the  doubly  lnked  list
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ head ​ ​Double  Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ ​​status.
​ ​*/
int destroy(node_t **head);

/**
​ ​* ​ ​@brief ​ returns  the  size  of  the  doubly  linked  list
​ ​*
​ ​* ​ returns  the  size  of  the  doubly  linked  list
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ head ​ Pointer ​ ​to ​ ​a ​ ​doubly  linked  list  node
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ ​​size.
​ ​*/
int size(node_t *head);

#endif /*  _DBLL_H_  */
