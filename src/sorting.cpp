//
// Created by DominicAnene on 1/19/19.
//

#include <hoarse_parition.h>

namespace sorting{

    void bubbleup(int* arr_ptr, size_t ptr_loc){
        if (ptr_loc > 0){
            (arr_ptr - ptr_loc) = &(arr_ptr - --ptr_loc);
            bubbleup(arr_ptr, --ptr_loc);
        }
    }


    void insert(int* arr_ptr, size_t ptr_loc){
        // To the left of ptr_loc is a sorted list
        // To the right of ptr_loc is not a sorted lst
        if (ptr_loc > 0){
            // & gives the address of the object. This is the thing that fixed.
            if (*(arr_ptr - ptr_loc) < *arr_ptr){
                T pivot_val = *arr_ptr;
                bubbleup(arr_ptr, ptr_loc) //shift everything forward by 1
                (arr_ptr - ptr_loc) = pivot_val; // then place the pivot in correct position.
                // insert then bubble up
            }
            else{
                // itereate.
            }
            insert(arr_ptr ,--ptr_loc);
        }
    }
}