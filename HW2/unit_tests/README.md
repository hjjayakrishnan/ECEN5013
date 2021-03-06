# cmocka example for ECEN 5013

* [cmocka](https://cmocka.org/)

* cmocka [API](https://api.cmocka.org/index.html)

cmocka is included in this repository as a git subtree. See
3rd-party/README.md for details.

## Requirements

* cmake - available through most package managers.

## Build

* building cmocka:

    ```SHELL
    make cmocka
    ```

    This will go into the 3rd-party libraries directory and call cmake
    correctly to build cmocka.

* building and running tests:

    ```SHELL
    make test
    ```
    
* building main executable

    ```SHELL
    make all
    ```
    
* cleaing up local build artifacts:

    ```SHELL
    make clean
    ```
    
* removing all generated files, including 3rd-party builds

    ```SHELL
    make clobber
    ```
    
## Source

Included source files are:

* db_ll.{h|c} - library for doubly linked list.

* test_dbll.c - unit tests for doubly linked list.

* main_ll.c - simple demo driver using library.

## Unit tests Perfomed

* test_insert_at_head - Insert at head of the doubly linked list.
* test_insert_at_middle - Insert at middle of the doubly linked list.
* test_insert_at_end - Insert at end of the doubly linked list
* test_search_data_present - Search for a data that is present in the doubly linked list
* test_search_data_not_present - Search for a data that is not present in the doubly linked list
* test_display_linkedList - Display all the nodes of the doubly linked list
* test_delete_linkedList - Free all the memory allocated to the double linked list
* test_delete_add_linkedList - Free memory and then re-add nodes 
