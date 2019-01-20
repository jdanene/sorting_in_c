//
// Created by DominicAnene on 1/19/19.
//

#pragma once

namespace sorting{

        void sort(int* arr_ptr, int arr_sz);

        void quicksort(int* arr_ptr, int arr_sz);

        void insertionsort(int* arr_ptr, int arr_sz);

        void insert(int* arr_ptr, size_t ptr_loc);

        void bubbleup(int* arr_ptr, size_t ptr_loc);
}
