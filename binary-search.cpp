
int binarySearch(long long arr[], int size, long long target, long long *operationCount);

long long binarySearchOperations = 0;

int binarySearch(long long arr[], int size, long long target, long long *operationCount) {
    int left = 0, right = size - 1;
    long long localCount = 0;
    
    while (left <= right) {
        localCount++;
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            *operationCount += localCount;
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    *operationCount += localCount;
    return -1; 
}
