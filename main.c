#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>


/*!
 * @function bubbleup
 * @abstract Inplace shift of array values between the initial `i' and `right` up by 1.
 * @param arr_ptr Pointer to the first element of the array
 * @param i
 * @param prev_val Value of array at `i'-1
 * @param right
 * */
void bubbleup(int* arr_ptr, int i, int prev_val, const int right){
    if (i <= right){
        int curr_val = *(arr_ptr + i);
        *(arr_ptr + i) = prev_val;
        bubbleup(arr_ptr, ++i,curr_val,right);
    }
}

/*!
 * @function insert
 * @abstract Inserts the pivot value into the correct place in the array segment.
 * @discussion Array values between `lowerIdx' and `right'-1 are assumed to be sorted;
 *            `lowerIdx' is the smallest value and `right'-1  is the largest value. The goal is to
 *             insert the current pivot value into the correct place.  To do this
 *             iterate from `lowerIdx' to `right'-1 to find correct place to insert the pivot value.
 * @param arr_ptr Pointer to the first element of the array
 * @param pivot_value The value of the current pivot.
 * @param left The index of value we are checking pivot against to see if we should insert pivot at this place.
 * @param right The index of the current pivot.
 * @result Inplace insertion of of pivot value
 * */
void insert(int * arr_ptr, const int pivot_value, int left, const int right){
    if (left < right){
        if (pivot_value < *(arr_ptr + left)){
            int temp = *(arr_ptr + left);
            *(arr_ptr + left) = pivot_value; // place the pivot in correct position
            bubbleup(arr_ptr, ++left, temp, right); // shift everything up by 1.
        }
        else{
            insert(arr_ptr, pivot_value, ++left, right);
        }
    }
}

/*!
 * @function insertion_sort
 * @discussion Insertion sort iterates, consuming one input element each repetition,
 *             and growing a sorted output list. At each iteration, insertion sort removes
 *             one element from the input data, finds the location it belongs within the sorted list,
 *             and inserts it there. It repeats until no input elements remain.
 * @param arr_ptr Pointer to the first element of the array
 * @param right The index of the current pivot.
 * @param lowerIdx Lower index threshold of array partition of interest.
 * @param upperIdx Upper index threshold of array partition of interest.
 * */
 void insertion_sort(int* arr_ptr, int right, int lowerIdx, const int upperIdx) {
    if (right <= upperIdx){
        if (right >= 1) {
            int pivot_value = *(arr_ptr + right);
            if (*(arr_ptr + (right - 1)) > pivot_value) {
                insert(arr_ptr, pivot_value, lowerIdx, right);
                insertion_sort(arr_ptr,++right, lowerIdx, upperIdx);
            }
            else {
                insertion_sort(arr_ptr, ++right, lowerIdx,upperIdx);
            }
        }
        else{
            insertion_sort(arr_ptr,++right,lowerIdx, upperIdx);
        }
    }
}

void swap(int* arr_ptr, int left, int right){
    int temp = *(arr_ptr+left);
    *(arr_ptr+left) = *(arr_ptr+right);
    *(arr_ptr+right) = temp;
}

int hoare_partition(int* arr_ptr, int left, int right, int pivot_val){
    if (left > right){
        return right;
    }
    else{
        if ((*(arr_ptr+left) > pivot_val) && (*(arr_ptr+right) <= pivot_val)){
            swap(arr_ptr, left, right);
            return hoare_partition(arr_ptr,++left, --right, pivot_val);
        }
        else{
            if (*(arr_ptr+left) <= pivot_val){
                ++left;
            }
            if (*(arr_ptr+right) > pivot_val){
                --right;
            }
            return hoare_partition(arr_ptr, left, right, pivot_val);
        }
    }
}

int hoare_partition_wrapper(int* arr_ptr, int lowerIdx, int upperIdx){
    if (upperIdx >= 0){
        int pivotIdx = (lowerIdx+upperIdx)/2;
        int pivot_val = *(arr_ptr+pivotIdx);
        *(arr_ptr+pivotIdx) = *(arr_ptr+lowerIdx);
        *(arr_ptr+lowerIdx) = pivot_val;

        int right = hoare_partition(arr_ptr, lowerIdx+1, upperIdx,pivot_val );

        *(arr_ptr+lowerIdx) = *(arr_ptr+right);
        *(arr_ptr+right) = pivot_val;

        // Elements located up to the right index will be <= pivot.
        return right;
    }
};

void quick_sort_varient(int* arr_ptr, int lowerIdx, int upperIdx){
    if (lowerIdx < upperIdx){
        int pivotIdx = hoare_partition_wrapper(arr_ptr, lowerIdx, upperIdx);
        if ((pivotIdx + 1 > 10) && ((upperIdx-pivotIdx + 1) > 10)){
            //printf("Case 1\n");
            quick_sort_varient(arr_ptr, lowerIdx, pivotIdx -1  );
            quick_sort_varient(arr_ptr, pivotIdx +1, upperIdx);
        }
        else if ((pivotIdx +1 <= 10) && ((upperIdx-pivotIdx + 1) > 10)){
            //printf("Case 2\n");
            insertion_sort(arr_ptr, lowerIdx, lowerIdx, pivotIdx -1);
            quick_sort_varient(arr_ptr, pivotIdx +1, upperIdx);
        }
        else if ((pivotIdx +1 > 10) && ((upperIdx-pivotIdx + 1) <= 10)){
            //printf("Case 3\n");
            quick_sort_varient(arr_ptr, lowerIdx, pivotIdx -1);
            insertion_sort(arr_ptr, pivotIdx +1, pivotIdx +1, upperIdx);
        }
        else{
            //printf("Case 4\n");
            insertion_sort(arr_ptr, lowerIdx, lowerIdx, pivotIdx -1);
            insertion_sort(arr_ptr, pivotIdx +1, pivotIdx +1, upperIdx);
        }
    }
}

void sort(int* arr_ptr, const int arr_sz){
    if (arr_sz> 0){
        quick_sort_varient(arr_ptr, 0, arr_sz-1);
    }
}

bool isarrayEqual(int arr1[], int arr2[],int n ,int m){
    if (n != m){
        return false;
    }
    for (int i=0; i<n; i++)
        if (arr1[i] != arr2[i]){
            return false;
        }
    return true;
}

int main() {


    //Test 1
    int arr[]={1,7,11,-99,15,10};
    int arr_sorted[] = {-99, 1, 7, 10, 11, 15};
    int n = sizeof (arr) / sizeof (int);
    int m = sizeof (arr_sorted) / sizeof (int);
    sort(arr, n);
    isarrayEqual(arr, arr_sorted, n, m);

    // Test 2
    int arr1[]={1,7,11,-99,15,10, 10, -4, 4,2,-66,5, 0, 2,90,100,17,35,211,-43};
    int arr1_sorted[] = {-99, -66, -43, -4, 0, 1, 2, 2, 4, 5, 7, 10, 10, 11, 15, 17, 35, 90, 100, 211};
    n = sizeof (arr1) / sizeof (int);
    m = sizeof (arr1_sorted) / sizeof (int);
    sort(arr1, n);
    isarrayEqual(arr1, arr1_sorted, n, m);

    // Test 3
    int arr2[]={1,7,11,-99,15,10, 10, -4, 4,2,-66,5, 0, 2,90,100,
                17,35,211,-43,454,6,54,-35,256,34,2,77,46,2,6773,2678,-776};
    int arr2_sorted[]= {-776, -99 , -66 ,-43 ,-35 ,-4, 0, 1, 2, 2, 2, 2, 4, 5,
                        6, 7, 10, 10, 11, 15, 17, 34, 35, 46, 54, 77, 90, 100, 211, 256, 454, 2678, 6773} ;

    n = sizeof (arr2) / sizeof (int);
    m = sizeof (arr2_sorted) / sizeof (int);
    sort(arr2, n);
    isarrayEqual(arr2, arr2_sorted, n, m);


    return 0;
}