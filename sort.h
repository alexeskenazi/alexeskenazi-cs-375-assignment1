#ifndef SORT_H
#define SORT_H

// Function declarations for merge sort
void merge(long long arr[], int left, int mid, int right);
void mergeSort(long long arr[], int left, int right);
long long mergeSortArray(long long arr[], int size);

// Global variable for operation counting
extern long long mergeSortOperations;

#endif