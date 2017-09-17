#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "db_ll.h"

void test_insert_at_head(void **state){

  node_t *head = NULL;
  enum dbll_status status = add_node_index(&head, 5, 0);
  destroy(&head); //freeing memory
  assert_true(status == SUCCESS);
}

void test_insert_at_middle(void **state){
  node_t *head = NULL;
  add_node(&head, 5);
  add_node(&head, 6);
  add_node(&head, 7);
  add_node(&head, 8);
  enum dbll_status status = add_node_index(&head, 10, 2); // 2 - middle
  display(head);
  assert_true(status == SUCCESS);
}

void test_insert_at_end(void **state){
  node_t *head = NULL;
  add_node(&head, 5);
  add_node(&head, 6);
  add_node(&head, 7);
  add_node(&head, 8);
  enum dbll_status status = add_node_index(&head, 10, 4); // 4 - end
  display(head);
  assert_true(status == SUCCESS);
}

void test_search_data_present(void **state){
  node_t *head = NULL;
  int where;
  add_node(&head, 5);
  add_node(&head, 6);
  add_node(&head, 7);
  add_node(&head, 8);
  enum dbll_status status = search(head,7,&where);
  // assert_int_equal(where, 2); // 2 is the position of 7
  assert_true((status == SUCCESS) && (where==2));
  display(head);

}

void test_search_data_not_present(void **state){
  node_t *head = NULL;
  int where;
  add_node(&head, 5);
  add_node(&head, 6);
  add_node(&head, 7);
  add_node(&head, 8);
  enum dbll_status status = search(head,9,&where);
  // assert_int_equal(where, 2); // 2 is the position of 7
  assert_true((status == FAILURE) && (where==NO_DATA));
  display(head);

}

void test_display_linkedList(void **state){
  node_t *head = NULL;
  add_node(&head, 5);
  add_node(&head, 6);
  add_node(&head, 7);
  add_node(&head, 8);
  enum dbll_status status = display(head);
  assert_true(status == SUCCESS);
}

void test_display_empty_linkedList(void **state){
  node_t *head = NULL;
  enum dbll_status status = display(head);
  assert_true(status == EMPTY);
}

void test_delete_linkedList(void **state){
  node_t *head = NULL;
  add_node(&head, 5);
  add_node(&head, 6);
  add_node(&head, 7);
  add_node(&head, 8);
  enum dbll_status status = destroy(&head);
  assert_true(status == SUCCESS);
}

void test_delete_add_linkedList(void **state){
  node_t *head = NULL;
  int node_count;
  add_node(&head, 5);
  add_node(&head, 6);
  enum dbll_status status = destroy(&head);
  add_node(&head, 7);
  add_node(&head, 8);
  node_count = size(head);
  assert_true(status == SUCCESS && node_count == 2);
}

void test_delete_empty_linkedList(void **state){
  node_t *head = NULL;
  enum dbll_status status = destroy(&head);
  assert_true(status == EMPTY);
}

int main(int argc, char **argv){

const struct CMUnitTest tests[]={
  cmocka_unit_test(test_insert_at_head),
  cmocka_unit_test(test_insert_at_middle),
  cmocka_unit_test(test_insert_at_end),
  cmocka_unit_test(test_search_data_present),
  cmocka_unit_test(test_search_data_not_present),
  cmocka_unit_test(test_display_linkedList),
  cmocka_unit_test(test_display_empty_linkedList),
  cmocka_unit_test(test_delete_linkedList),
  cmocka_unit_test(test_delete_add_linkedList),
  cmocka_unit_test(test_delete_empty_linkedList)
};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
