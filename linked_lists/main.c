// gcc main.c sll.c -o main

#include "sll.h"
#include <stdio.h>

int main(void) {
    // printf("sizeof(\"George\") = %ld\n", sizeof("George"));
    // char arr[40] = "George";
    // printf("sizeof(arr) = %ld\n", sizeof(arr));

    // int (*func_ptr)(int) = add_in_the_beginning;
    int (*func_ptr)(int) = add_at_the_end;

    list_init(100);

    func_ptr(101);
    func_ptr(102);
    func_ptr(103);
    traverse();

    printf("\nDoes 100 exist ? : %d\n", exists(100));
    printf("Does 101 exist ? : %d\n", exists(101));
    printf("Does 102 exist ? : %d\n", exists(102));
    printf("Does 103 exist ? : %d\n", exists(103));
    printf("Does 104 exist ? : %d\n", exists(104));
    printf("Does 105 exist ? : %d\n", exists(105));

    //delete_node(100);
    //printf("\nDoes 100 exist ? : %d\n", exists(100));
    
    /*
    delete_node(101);
    printf("Does 101 exist ? : %d\n", exists(101));
    delete_node(102);
    printf("Does 102 exist ? : %d\n", exists(102));
    delete_node(100);
    printf("Does 100 exist ? : %d\n", exists(100));
    */

    //delete_node(103);
    //printf("\nDoes 103 exist ? : %d\n", exists(103));

    insert(102, 50);
    printf("Does 50 exist ? : %d\n", exists(50));
    insert(103, 104);
    printf("Does 104 exist ? : %d\n", exists(104));
    insert(50, 51);
    printf("Does 51 exist ? : %d\n", exists(51));

    insert(106, 55);
    printf("Does 55 exist ? : %d\n", exists(55));

    traverse();

    return SUCCESS;
}