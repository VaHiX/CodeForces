// Problem: CF 1952 C - They Have Fooled
// https://codeforces.com/contest/1952/problem/C

#include <stdio.h>

/*
 * Code Purpose: This program implements a simple lookup table solution to retrieve values from a predefined array.
 *               Given an index n, it returns the value at that index in the pre-defined array v.
 * 
 * Algorithms/Techniques: Direct array indexing (lookup table approach)
 * Time Complexity: O(1) - Constant time lookup
 * Space Complexity: O(1) - Fixed space usage (13 elements array + 1 input variable)
 */

int main() {
  long v[13] = {10, 10, 8, 9, 8, 7, 7, 7, 7, 0, 9, 6, 8}; // Initialize array with predefined values
  long n; // Declare variable to store user input index
  scanf("%ld", &n); // Read the index from stdin
  printf("%ld\n", v[n]); // Print the value at index n from array v
}

// https://github.com/VaHiX/codeForces/