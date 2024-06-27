//
//  main.c
//  iterative_qsort
//
//  Created by Даниил on 30.05.2024.
//
#include <stdio.h>
#include <stdlib.h>


#define SIZE 9

typedef struct stack{
    size_t len;
    int* sub_array;
    struct stack* next;
} stack;

void sort(stack**);

void push_stack(stack**, int*, size_t);
stack* pop_stack(stack*);
char are_same(int*, size_t);


int main(int argc, char* argv[]){
    int array[SIZE] = {8, 1, 7, 5, 3, 9, 4, 6, 6};
    int res[SIZE] = {0}; int res_len = 0;
    stack* sub_arrays = NULL;
    push_stack(&sub_arrays, array, SIZE);
    
    while(sub_arrays != NULL){
        sort(&sub_arrays);
        while(sub_arrays != NULL && are_same(sub_arrays->sub_array, sub_arrays->len)){
            for(int i = 0; i < sub_arrays->len; i++){
                res[res_len] = sub_arrays->sub_array[0];
                res_len++;
            }
            sub_arrays = pop_stack(sub_arrays);
        }
    }
    
    for(int i = 0; i < SIZE; i++){
        printf("%d ", res[i]);
    }
    
    return 0;
}

char are_same(int* array, size_t len){
    char flag = 1;
    char number = array[0];
    for(int i = 0; i < len; i++){
        if(number != array[i]) flag = 0;
    }
    return flag;
}

void push_stack(stack** sub_arrays, int* data, size_t len){
    stack* ptr = malloc(sizeof(stack));
    ptr->len = len;
    ptr->sub_array = data;
    ptr->next = *sub_arrays;
    *sub_arrays = ptr;
}

stack* pop_stack(stack* top){
    if (top == NULL)
        return top;
    stack *ptr_next = top->next;
    free(top);
    top = ptr_next;
    return top;
}

void sort(stack** sub_arrays){
    int* array = (*sub_arrays)->sub_array;
    size_t len = (*sub_arrays)->len;
    *sub_arrays = pop_stack(*sub_arrays);
    int left_array[SIZE] = {0}; int la_size = 0;
    int right_array[SIZE] = {0}; int ra_size = 0;
    int pivot[SIZE] = {0}; int p_size = 0;
    
    pivot[0] = array[0];
    
    for(int i = 0; i < len; i++){                  //O(n)
        if(array[i] > pivot[0]){
            right_array[ra_size++] = array[i];
        }
        else if(array[i] < pivot[0]){
            left_array[la_size++] = array[i];
        }else{
            pivot[p_size++] = array[i];
        }
    }
    int* new_left_array = malloc(la_size*sizeof(int));
    for(int i = 0; i < la_size; i++) new_left_array[i] = left_array[i];
    
    int* new_right_array = malloc(ra_size*sizeof(int));
    for(int i = 0; i < ra_size; i++) new_right_array[i] = right_array[i];
    
    int* new_pivot = malloc(p_size*sizeof(int));
    for(int i = 0; i < p_size; i++) new_pivot[i] = pivot[i];
    

    if (la_size != 0) push_stack(sub_arrays, new_left_array, la_size);
    if (p_size != 0) push_stack(sub_arrays, new_pivot, p_size);
    if (ra_size != 0) push_stack(sub_arrays, new_right_array, ra_size);
}
