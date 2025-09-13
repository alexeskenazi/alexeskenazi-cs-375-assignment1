// This program reads an inputfile of numbers.
// The input file has on number per line.
// The program prints out the squares of the input file numbers
// to the output file.
// The output file has on numner per line.

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cassert>

using namespace std;

#define BUFSIZE 1000

long long findNumLines(FILE *fp);

int writeDestFile(FILE *fp);

char * sortABCarray(char *data, int numLines);

void TestSortABCarray();

void testFindKeyAsDifference();

void testFindKeyAsDifference();


FILE *srcFP, *destFP;
long long numLines, *data;

int main(int argc, char *argv[]) {

  // TestSortABCarray();
  testFindKeyAsDifference();

  int i;
  char str[BUFSIZE];

  if(argc!=3) {
    printf("Usage: progname <input_file> <output_file>");
    exit(0);
  }
  
  if((srcFP =fopen(argv[1], "r")) == NULL) {
    perror("Error opening input file");
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
  
  while(!feof(srcFP)) {

    // the first non-blank line that is not a comment has been read

    int len = strlen(str);
    if (len > 0) { 
      sortABCarray(str, len);
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
    printf("Read data[%d]=%lld\n", dataIndex, data[dataIndex]);
    dataIndex++;
  }


  if((destFP = fopen(argv[2], "w")) == NULL) {
    perror("Error opening output file");
    exit(0);
  }

  if((destFP = fopen(argv[2], "w")) == NULL) {
    perror("Error opening output file");
    exit(0);
  }

  
  writeDestFile(destFP);

  fclose(srcFP);
  fclose(destFP);
}

int writeDestFile(FILE *fp) {
  long long i;
  for(i = 0; i < numLines; i++)
    fprintf(fp, "%lld\n", data[i]*data[i]);
  return 0;
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

char * sortABCarray(char *str, int len) {
    // Remove newline if present
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
        len--;
    }
    
    int low = 0;       
    int mid = 0;       
    int high = len - 1;  

    printf("Initial data: %s\n", str);

    while (mid <= high) {  
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
    printf("Sorted data: %s\n", str);
    return str;
}


void TestSortABCarray() {
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

    sortABCarray(test0, strlen(test0));
    assert(strcmp(test0, test0_expected) == 0);

    sortABCarray(test1, strlen(test1));
    assert(strcmp(test1, test1_expected) == 0);

    sortABCarray(test2, strlen(test2));
    assert(strcmp(test2, test2_expected) == 0);
    sortABCarray(test3, strlen(test3));
    assert(strcmp(test3, test3_expected) == 0);
    sortABCarray(test4, strlen(test4));
    assert(strcmp(test4, test4_expected) == 0);

    sortABCarray(test5, strlen(test5));
    assert(strcmp(test5, test5_expected) == 0);
    sortABCarray(test6, strlen(test6));
    assert(strcmp(test6, test6_expected) == 0);
    sortABCarray(test7, strlen(test7));
    assert(strcmp(test7, test7_expected) == 0);
    sortABCarray(test8, strlen(test8));
    assert(strcmp(test8, test8_expected) == 0);

    sortABCarray(test9, strlen(test9));
    assert(strcmp(test9, test9_expected) == 0);
    sortABCarray(test10, strlen(test10));
    assert(strcmp(test10, test10_expected) == 0);
    sortABCarray(test11, strlen(test11));
    assert(strcmp(test11, test11_expected) == 0);

    sortABCarray(test12, strlen(test12));
    assert(strcmp(test12, test12_expected) == 0);
    sortABCarray(test13, strlen(test13));
    assert(strcmp(test13, test13_expected) == 0);

    sortABCarray(test14, strlen(test14));
    assert(strcmp(test14, test14_expected) == 0);
    sortABCarray(test15, strlen(test15));
    assert(strcmp(test15, test15_expected) == 0);
    sortABCarray(test16, strlen(test16));
    assert(strcmp(test16, test16_expected) == 0);

    sortABCarray(test17, strlen(test17));
    assert(strcmp(test17, test17_expected) == 0);
    sortABCarray(test18, strlen(test18));
    assert(strcmp(test18, test18_expected) == 0);

    sortABCarray(test19, strlen(test19));
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


bool findKeyAsDifference(long long *data, int numLines) {
    bool found = false;

    for (int i = 0; i < numLines; i++) {
    
      for (int j = 0; j < numLines; j++) {
    
        if (i != j) {
    
          long long diff = data[i] - data[j];
    
          for (int k = 0; k < numLines; k++) {
    
            if (k != i && k != j && data[k] == diff) {
              printf("Found: %lld = %lld - %lld\n", diff, data[i], data[j]);
              found = true;
            }
          }
        }
      }
    }
    return found;
}

void testFindKeyAsDifference() {
    long long testData1[] = {14, 89, 18, 105, 23, 4, 35, 99, 67, 76, 198, 20, 5, 38, 55, 2, 30, 19, 487, 11, 40, 10, 13, 27, 22, 45, 37, 231, 46, 17, 731, 49, 167, 234, 59, 91, 179, 201};
    int size1 = sizeof(testData1) / sizeof(testData1[0]);
    findKeyAsDifference(testData1, size1);
}

