#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cassert>
#include <cmath>

using namespace std;

#define BUFSIZE 1000

long long findNumLines(FILE *fp);

char * sortABCarray(FILE *fp, char *data, int numLines);

void testSortABCarray();

void testFindKeyAsDifference();

bool findKeyAsDifference(FILE *fp, long long *data, int numLines);

long long mergeSortArray(long long arr[], int size);

int binarySearch(long long arr[], int size, long long target, long long *operationCount);


FILE *srcFP, *destFP;
long long numLines, *data;

int main(int argc, char *argv[]) {

  int i;
  char str[BUFSIZE];

  if(argc<3) {
    printf("Usage: progname <input_file> <output_file>");
    exit(0);
  }

  if(argc>3) {
    if(strcmp(argv[3], "test") == 0) {
      testSortABCarray();
      testFindKeyAsDifference();
      exit(0);
    }
  }
  
  if((srcFP =fopen(argv[1], "r")) == NULL) {
    perror("Error opening input file");
    exit(0);
  }

  if((destFP = fopen(argv[2], "w")) == NULL) {
    perror("Error opening output file");
    exit(0);
  }
  
  numLines = findNumLines(srcFP); //
  

  // Find the fist non-blank line that is not a comment
  for(i=0; i<numLines; i++) {
    fgets(str, BUFSIZE, srcFP);

    // Skip blank lines and lines with // only
    if((str[0] == '\n') || (str[0] == ' ') || ((str[0] == '/') && (str[1] == '/'))) {
      i--;
      continue;
    }

    break;
  }


  // while the read input is not empty or "//Part B.2" read and sort

  fprintf(destFP, "//Part B.1 \n\n");
  printf("//Part B.1 \n\n");
  
  while(!feof(srcFP)) {

    // the first non-blank line that is not a comment has been read

    int len = strlen(str);
    if (len > 0) { 
      sortABCarray(destFP, str, len);
    }
    
    fgets(str, BUFSIZE, srcFP);

    // Skip blank lines
    if(( str[0] == '\n') || (str[0] == ' ') ) {
      str[0] = '\0';
      continue;
    }

    // Stop if we reach "//Part B.2"
    if(strncmp(str, "//Part B.2", 10) == 0) {
      break;
    }

  }

  // We are at the beginning of Part B.2
  data = (long long *) malloc(numLines * sizeof(long long));
  int dataIndex = 0;


  // Read the data from the input file
  for(i=0; i<numLines; i++) {

    fgets(str, 100, srcFP);

    // Skip blank lines and lines with // only
    if((str[0] == '\n') || (str[0] == ' ') || ((str[0] == '/') && (str[1] == '/'))) {
      i--;
      continue;
    }

    // stop eof file
    if(feof(srcFP)) {
      break;
    }

    // Read a number from the input file
    sscanf(str, "%lld", &(data[dataIndex]));
    // printf("Read data[%d]=%lld\n", dataIndex, data[dataIndex]);
    dataIndex++;
  }

  fprintf(destFP, "\n\n// Part B.2\n\n");
  printf("\n\n// Part B.2\n\n");

  findKeyAsDifference(destFP, data, dataIndex);

  fclose(srcFP);
  fclose(destFP);
}


//returns file size as number of lines in the file
long long findNumLines(FILE *fp) {

  long long numLines = 0;
  char str[100];

  while(!feof(fp)) {
    fgets(str, 100, fp);
    numLines++;
  }
  
  numLines--;//the above increments count even when EOF reached
  
  if(fseek(fp, 0L, SEEK_SET) == EOF) {
    perror("Error while seeking to begining of file");
    exit(0);
  }

  return numLines;
}   



// Suppose that we have an array of n data records to sort and that the key of each record
// has the value either A, B, or C. Give a linear-time algorithm with an appropriate data 
// structure for sorting the n data records in place (A…B….C…). 
// Use no storage of more than constant size in addition to the storage provided by 
// the array. Show the worst-case time complexity and the space cost.
// For example: input ABACBACACBBAC  output AAAAABBBBCCCC

void swapChars(char &x, char &y) {
    char temp = x;
    x = y;
    y = temp; 
}

char * sortABCarray(FILE *fp, char *str, int len) {
    long long count = 0;
    // Remove newline if present
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
        len--;
    }
    
    int low = 0;       
    int mid = 0;       
    int high = len - 1;  

    // printf("Initial data: %s\n", str);

    while (mid <= high) {  
        count++;
        switch (str[mid]) {
            case 'A':
                swapChars(str[low++], str[mid++]);
                break;
            case 'B':
                mid++;
                break;
            case 'C':
                swapChars(str[mid], str[high--]);
                break;
        }
    }
    if(fp) fprintf(destFP, "%s\n\n", str);
    if(fp) fprintf(destFP, "Running time: %lld\n", count);

    printf("%s\n\n", str);
    printf("Running time: %lld\n", count);
    return str;
}


void testSortABCarray() {
    // Representative, non-duplicative set

    char test0[]  = "";
    char test0_expected[]  = "";

    char test1[]  = "ABACBACACBBAC";
    char test1_expected[]  = "AAAAABBBBCCCC";

    char test2[]  = "A";
    char test2_expected[]  = "A";
    char test3[]  = "B";
    char test3_expected[]  = "B";
    char test4[]  = "C";
    char test4_expected[]  = "C";

    char test5[]  = "AA";
    char test5_expected[]  = "AA";
    char test6[]  = "AB";
    char test6_expected[]  = "AB";
    char test7[]  = "AC";
    char test7_expected[]  = "AC";
    char test8[]  = "BC";
    char test8_expected[]  = "BC";

    char test9[]  = "AAB";
    char test9_expected[]  = "AAB";
    char test10[] = "ABB";
    char test10_expected[] = "ABB";
    char test11[] = "ACC";
    char test11_expected[] = "ACC";

    char test12[] = "ABC";
    char test12_expected[] = "ABC";
    char test13[] = "CBA";
    char test13_expected[] = "ABC";

    char test14[] = "AAABBBCCC";
    char test14_expected[] = "AAABBBCCC";
    char test15[] = "CCCBBBAAA";
    char test15_expected[] = "AAABBBCCC";
    char test16[] = "ABCABCABC";
    char test16_expected[] = "AAABBBCCC";

    char test17[] = "BBBBBBAAAAAA";
    char test17_expected[] = "AAAAAABBBBBB";
    char test18[] = "AAAAAACCCCCC";
    char test18_expected[] = "AAAAAACCCCCC";

    char test19[] = "AAAAABBBCCC";
    char test19_expected[] = "AAAAABBBCCC";

    sortABCarray( NULL, test0, strlen(test0));
    assert(strcmp(test0, test0_expected) == 0);

    sortABCarray( NULL, test1, strlen(test1));
    assert(strcmp(test1, test1_expected) == 0);

    sortABCarray( NULL, test2, strlen(test2));
    assert(strcmp(test2, test2_expected) == 0);
    sortABCarray( NULL, test3, strlen(test3));
    assert(strcmp(test3, test3_expected) == 0);
    sortABCarray( NULL, test4, strlen(test4));
    assert(strcmp(test4, test4_expected) == 0);

    sortABCarray( NULL, test5, strlen(test5));
    assert(strcmp(test5, test5_expected) == 0);
    sortABCarray( NULL, test6, strlen(test6));
    assert(strcmp(test6, test6_expected) == 0);
    sortABCarray( NULL, test7, strlen(test7));
    assert(strcmp(test7, test7_expected) == 0);
    sortABCarray( NULL, test8, strlen(test8));
    assert(strcmp(test8, test8_expected) == 0);

    sortABCarray( NULL, test9, strlen(test9));
    assert(strcmp(test9, test9_expected) == 0);
    sortABCarray( NULL, test10, strlen(test10));
    assert(strcmp(test10, test10_expected) == 0);
    sortABCarray( NULL, test11, strlen(test11));
    assert(strcmp(test11, test11_expected) == 0);

    sortABCarray( NULL, test12, strlen(test12));
    assert(strcmp(test12, test12_expected) == 0);
    sortABCarray( NULL, test13, strlen(test13));
    assert(strcmp(test13, test13_expected) == 0);

    sortABCarray( NULL, test14, strlen(test14));
    assert(strcmp(test14, test14_expected) == 0);
    sortABCarray( NULL, test15, strlen(test15));
    assert(strcmp(test15, test15_expected) == 0);
    sortABCarray( NULL, test16, strlen(test16));
    assert(strcmp(test16, test16_expected) == 0);

    sortABCarray( NULL, test17, strlen(test17));
    assert(strcmp(test17, test17_expected) == 0);
    sortABCarray( NULL, test18, strlen(test18));
    assert(strcmp(test18, test18_expected) == 0);

    sortABCarray( NULL, test19, strlen(test19));
    assert(strcmp(test19, test19_expected) == 0);
}


// B.2.  (12%) Given an array containing n keys, design an algorithm to determine 
// whether there is such a key that is equal to the difference between the 
// other two keys in the array. Explain the worst-case time complexity and space cost. 
// (Your algorithm should be no worse than O(n2lgn). Implement your algorithm with a 
// proper data structure and print out all the keys that are equal to the difference 
// between the other two keys in the array, and print out the corresponding two keys; 
// Print out the running time.

// Example data for test:
// [14,  89,  18,  105,  23,   4,   35,   99,   67,  76,  198,   20,   5,  38,   55,   2,  30,   19,   487,  11,  40,  10,  13,  27,  22,   45,  37, 231, 46, 17,  731, 49,  167, 234, 59, 91, 179, 201]


#include "sort.h"
#include "binary-search.h"

bool findKeyAsDifference(FILE *fp, long long *data, int numLines) {
    bool found = false;
    long long count = 0;
    
    
    long long *sorted_data = (long long*)malloc(numLines * sizeof(long long));
    for (int i = 0; i < numLines; i++) {
        sorted_data[i] = data[i];
    }
    
    // Sort the array using merge sort. O(n log n)
    long long sortOperations = mergeSortArray(sorted_data, numLines);
    count += sortOperations;
    
    // For each pair (i,j), check if their difference exists in the array. O(n^2 log n)
    for (int i = 0; i < numLines; i++) { // O(n)
        for (int j = i + 1; j < numLines; j++) { // O(n)
            count++;
            
            long long diff = sorted_data[j] - sorted_data[i];
            
            // Binary search for diff in the sorted array is O(log n)
            long long binarySearchOps = 0;
            int foundIndex = binarySearch(sorted_data, numLines, diff, &binarySearchOps);
            count += binarySearchOps;
            
            if (foundIndex != -1) {
                if (fp) fprintf(fp, "%lld-%lld=%lld\n", sorted_data[j], sorted_data[i], diff);
                printf("%lld-%lld=%lld\n", sorted_data[j], sorted_data[i], diff);
                found = true;
            }
        }
    }
    
    free(sorted_data);
    
    if (fp) fprintf(destFP, "\nRunning time: %lld\n", count);
    printf("\nRunning time: %lld\n", count);
    printf("for n= %d, n^2 log n: %lld\n", numLines, (long long)(numLines * numLines * log2(numLines)));

    return found;
}

void testFindKeyAsDifference() {
    printf("Testing findKeyAsDifference function:\n");
    long long testData1[] = {14, 89, 18, 105, 23, 4, 35, 99, 67, 76, 198, 20, 5, 38, 55, 2, 30, 19, 487, 11, 40, 10, 13, 27, 22, 45, 37, 231, 46, 17, 731, 49, 167, 234, 59, 91, 179, 201};
    int size1 = sizeof(testData1) / sizeof(testData1[0]);
    findKeyAsDifference(NULL, testData1, size1);


    printf("-----------\n");
    long long testData2[] = {14, 28};
    int size2 = sizeof(testData2) / sizeof(testData2[0]);
    findKeyAsDifference(NULL, testData2, size2);

    printf("-----------\n");
    long long testData3[] = {14, 14, 0};
    int size3 = sizeof(testData3) / sizeof(testData3[0]);
    findKeyAsDifference(NULL, testData3, size3);

    printf("-----------\n");
    long long testData4[] = {1, 2, 3, 4, 5};
    int size4 = sizeof(testData4) / sizeof(testData4[0]);
    findKeyAsDifference(NULL, testData4, size4);

    printf("-----------\n");
    long long testData5[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int worstCaseSize = sizeof(testData5) / sizeof(testData5[0]);
    printf("Testing with %d prime numbers (should find few/no matches):\n", worstCaseSize);
    findKeyAsDifference(NULL, testData5, worstCaseSize);

}

