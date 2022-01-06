#include "sorting.h"


void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, void*)){
//    printf("-------------- start: [%d-%d] ---------------   V\n", start, stop - 1);
    if (start >= stop - 1) {
//        printf("-------------- return: [%d-%d] --------------   ^\n", start, stop - 1);
        return;
    }
//    printArr(arr, start, stop);
    int pivot = start;
//    printf("----------- pivot selection: %d ------------\n", arr[pivot]);
    int i = start + 1, j = stop - 1;
    while (i < j) {
        // true if arr[i] <= arr[pivot]
        while (compare(&arr[i], &arr[pivot]) && i < stop - 1) {
            i++;
        }
        // True if arr[j] > arr[pivot]
        while (compare(&arr[j], &arr[pivot])) {
            j--;
        }
        if (i < j) {
//            printf("--------- swap: %d <-> %d [%d <-> %d] ---------\n", arr[i], arr[j], i, j);
            swap(arr, i, j);
        }
    }
//    printf("------ pivot back: %d <-> %d [%d <-> %d] ------\n", arr[pivot], arr[j], pivot, j);
    swap(arr, pivot, j);
//    printArr(arr, start, stop);
    quicksort(arr, start, j, swap, compare);
//    printArr(arr, start, stop);
    quicksort(arr, i, stop, swap, compare);
//    printArr(arr, start, stop);
//    printf("-------------- return: [%d-%d] --------------   ^\n", start, stop - 1);
    }

