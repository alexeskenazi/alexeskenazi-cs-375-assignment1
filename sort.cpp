#include <stdlib.h>
#include "sort.h"

long long mergeSortOperations = 0;

void merge(long long arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    long long *leftArray = (long long*)malloc(n1 * sizeof(long long));
    long long *rightArray = (long long*)malloc(n2 * sizeof(long long));
    
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
        mergeSortOperations++; 
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[mid + 1 + j];
        mergeSortOperations++;
    }
    
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
    
    free(leftArray);
    free(rightArray);
}

void mergeSort(long long arr[], int left, int right) {
    if (left < right) {
        mergeSortOperations++;
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

long long mergeSortArray(long long arr[], int size) {
    mergeSortOperations = 0;
    mergeSort(arr, 0, size - 1);
    return mergeSortOperations;
}