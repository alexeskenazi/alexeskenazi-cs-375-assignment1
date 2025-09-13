# CS375 Assignment 1 - Programming Part

By Alex Eskenazi

## How to Run the Program

1. **Compile the program:**

   ```bash
   make
   ```

2. **Run the program:**

   ```bash
   ./submission inputFile.txt outputFile.txt
   ```

3. **Or compile and run in one step:**

   ```bash
   make run
   ```

4. **Run unit tests:**

   ```bash
   make test
   ```

5. **Clean build files:**

   ```bash
   make clean
   ```

## Sample Input/Output

**Input file format:**
([sample input file](2025Fall_SampleInputOutputCode_TA/input.txt))

**Output file format:**
([sample output file](2025Fall_SampleInputOutputCode_TA/output.txt))

## Algorithm Explanations

### Part B.1: Sorting A, B, C Characters

Sorts characters so all A's come first, then all B's, then all C's.

**Algorithm:**

- Use three pointers: low, mid, high
- Move A's to the left, C's to the right, B's stay in middle
- Each character is looked at only once so we get O(n)

**Time Complexity:** O(n) - linear time

**Space Complexity:** O(1) - only uses a few variables which are constant size.

### Part B.2: Finding Key as Difference

Find numbers in the array where one number equals the difference of two other numbers.

**Algorithm Steps:**

1. **Sort the array** using merge sort - O(n log n)
2. **For every pair of numbers** (i, j) - O(n²)
3. **Calculate their difference** - O(1)
4. **Search for that difference** in the sorted array using binary search - O(log n)
5. **If found, print the result** - O(1)

**Time Complexity Analysis:**

- Sorting: O(n log n)
- Nested loops: O(n²)
- Binary search inside loops: O(log n)

- Total: O(n log n) + ( O(n²)O(n log n)) -> O(n²)O(n log n) -> O(n² log n)
- **Total: O(n² log n)**

**Space Complexity:** O(n) - for the sorted copy of the array
