// This program reads an inputfile of numbers.
// The input file has on number per line.
// The program prints out the squares of the input file numbers
// to the output file.
// The output file has on numner per line.

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

long long findNumLines(FILE *fp);

int writeDestFile(FILE *fp);

char * sortABCarray(char *data, int numLines);


FILE *srcFP, *destFP;
long long numLines, *data;

int main(int argc, char *argv[]) {

  int i;
  char str[1000];

  if(argc!=3) {
    printf("Usage: progname <input_file> <output_file>");
    exit(0);
  }
  
  if((srcFP =fopen(argv[1], "r")) == NULL) {
    perror("Error opening input file");
    exit(0);
  }
  
  numLines = findNumLines(srcFP); //
  
  data = (long long *) malloc(numLines * sizeof(long long));

  for(i=0; i<numLines; i++) {
    fgets(str, 100, srcFP);

    // Skip blank lines and lines with // only
    if((str[0] == '\n') || ((str[0] == '/') && (str[1] == '/'))) {
      i--;
      continue;
    }

    // sscanf(str, "%lld", &(data[i]));
    // The first line should container the input string for sorting
    break;
  }


  int len = strlen(str);
  sortABCarray(str, len);


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
