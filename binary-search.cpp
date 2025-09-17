


#include "binary-search.h"

// Operation counter
long long binarySearchOperations = 0;

int binarySearch(long long arr[], int size, long long target, long long *operationCount) {
    int left = 0, right = size - 1;

    long long localCount = 0;
    
    while (left <= right) {
        // count this as one operation
        localCount++;
        
        // find the middle element
        int mid = left + (right - left) / 2;
        
        // did we find it?
        if (arr[mid] == target) {
            // yes! add our count and return where we found it
            *operationCount += localCount;
            return mid;
        } 
        // the middle is too small, so look in the right half
        else if (arr[mid] < target) {
            left = mid + 1;
        } 
        // the middle is too big, so look in the left half
        else {
            right = mid - 1;
        }
    }
    
    // we didn't find it
    *operationCount += localCount;
    return -1; 
}
