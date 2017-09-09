/*****************************************************************************
​ ​* ​ ​Copyright ​ ​(C) ​ ​2017 ​ ​by ​ ​Alex ​ ​Fosdick
​ ​*
​ ​* ​ ​Redistribution, ​ ​modification ​ ​or ​ ​use ​ ​of ​ ​this ​ ​software ​ ​in ​ ​source ​ ​or ​ ​binary
​ ​* ​ ​forms ​ ​is ​ ​permitted ​ ​as ​ ​long ​ ​as ​ ​the ​ ​files ​ ​maintain ​ ​this ​ ​copyright. ​ ​Users ​ ​are
​ ​* ​ ​permitted ​ ​to ​ ​modify ​ ​this ​ ​and ​ ​use ​ ​it ​ ​to ​ ​learn ​ ​about ​ ​the ​ ​field ​ ​of ​ ​embedded
​ ​* ​ ​software. ​ ​Alex ​ ​Fosdick ​ ​and ​ ​the ​ ​University ​ ​of ​ ​Colorado ​ ​are ​ ​not ​ ​liable ​ ​for
​ ​* ​ ​any ​ ​misuse ​ ​of ​ ​this ​ ​material.
​ ​*
*****************************************************************************/
/**
​ ​* ​ ​@file ​ circ_buffer.h
​ ​* ​ ​@brief ​ ​API for a circular buffer data structure
​ ​*
​ ​* ​ ​This ​ ​header ​ ​file ​ ​provides ​ ​an ​ ​abstraction ​ ​of ​ ​reading ​ ​and
​ ​* ​ ​writing ​ ​to ​ ​memory ​ ​via ​ ​function ​ ​calls.
​ ​*
​ ​* ​ ​@author ​ Jayakrishnan HJ
​ ​* ​ ​@date ​ ​September ​ 8 ​ ​2017
​ ​* ​ ​@version ​ ​1.0
​ ​*
​ ​*/
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

/**
​ ​* ​ ​@brief ​ Checks  if  buffer  is  full
​ ​*
​ ​* ​ ​Given ​ ​a ​ ​double  Pointer  to  the  buffer
​ ​* ​ this  will  return  if  the  buffer  is  full
​ ​*
​ ​* ​ ​@param ​ ​ptr ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ bool  if  full  or  not.
​ ​*/
bool is_buffer_full(circ_buffer **c1);

/**
​ ​* ​ ​@brief ​ Checks  if  buffer  is  empty
​ ​*
​ ​* ​ ​​Given ​ ​a ​ ​double  Pointer  to  the  buffer
​ ​* ​ this  will  return  if  the  buffer  is  empty
​ ​*
​ ​* ​ ​@param ​ ​ptr ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ bool  if  empty  or  not.
​ ​*/
bool is_buffer_empty(circ_buffer **c1);

/**
​ ​* ​ ​@brief ​ add  element  to  circular  buffer
​ ​*
​ ​* ​ Adds  the  input  passed  to  the  circular  buffer
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ c1 ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​ ​@param ​ ​in ​ ​Add  element  to  the  circular  buffer
​ ​*
​ ​* ​ ​@return ​ ​​status.
​ ​*/
int add_element(int in,circ_buffer **c1);

/**
​ ​* ​ ​@brief  remove  element  from  circular  buffer
​ ​*
​ ​* ​ remove  element  from  circular  buffer
 *
​ ​*
​ ​* ​ ​@param ​ c1 ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ ​​status.
​ ​*/
int remove_element(circ_buffer **c1);

/**
​ ​* ​ ​@brief ​ displays  the  elements  in  the  circular  buffer
​ ​*
​ ​* ​ brief ​ displays  the  elements  in  the  circular  buffer
​ ​* ​
​ ​*
​ ​* ​ ​@param ​ ​c1 ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ ​void.
​ ​*/
void dump(circ_buffer *c1);

/**
​ ​* ​ ​@Initializes   circular  buffer
​ ​*
​ ​* ​ ​Initialize  heap  space  for  buffer  and  struct
​ ​* ​ ​and  initializes  values
​ ​*
​ ​* ​ ​@param ​ c1 ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​ ​@param ​
​ ​*
​ ​* ​ ​@return ​ ​status.
​ ​*/
int init_buffer(circ_buffer **c1);

/**
​ ​* ​ ​@brief ​ ​destroy  the  buffer
​ ​*
​ ​* ​ ​Frees  the  heap  space  taken  by  the  buffer  and  struct
​ ​* ​ ​
​ ​*
​ ​* ​ ​@param ​ ​ ​ ​c1 ​ ​Double  Pointer ​ ​to ​ ​a ​ ​circular  buffer
​ ​* ​
​ ​*
​ ​* ​ ​@return ​ ​void.
​ ​*/
void destroy(circ_buffer **c1);

#endif
