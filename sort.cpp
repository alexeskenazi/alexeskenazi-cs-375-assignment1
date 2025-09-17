#include <stdlib.h>
#include "sort.h"

// count operations
long long mergeSortOperations = 0;

// Merge two subarrays of arr[]
// Firs subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(long long arr[], int left, int mid, int right) {
    // sizes of left and right subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // temp arrays
    long long *leftArray = (long long*)malloc(n1 * sizeof(long long));
    long long *rightArray = (long long*)malloc(n2 * sizeof(long long));
    
    // copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
        mergeSortOperations++; 
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[mid + 1 + j];
        mergeSortOperations++;
    }
    
    // merge the temp arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        mergeSortOperations++;
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // copy remaining elements
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
        mergeSortOperations++;
    }
    
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
        mergeSortOperations++;
    }
    
    // clean up memory
    free(leftArray);
    free(rightArray);
}

// Recursive merge sort
void mergeSort(long long arr[], int left, int right) {
    if (left < right) {
        mergeSortOperations++;
        // find middle
        int mid = left + (right - left) / 2;
        
        // sort left and right halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // merge them back together
        merge(arr, left, mid, right);
    }
}

// Wrapper
long long mergeSortArray(long long arr[], int size) {
    mergeSortOperations = 0;
    mergeSort(arr, 0, size - 1);
    return mergeSortOperations;
}