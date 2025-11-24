// Problem: CF 1984 A - Strange Splitting
// https://codeforces.com/contest/1984/problem/A

/*
Purpose: 
    This code solves the "Strange Splitting" problem where we need to color elements of a sorted array 
    into red and blue such that the ranges of red and blue elements are different, and each color has at least one element.
    
    The algorithm works as follows:
    - If all elements in the array are equal, it's impossible to split into two sets with different ranges → "NO"
    - Otherwise, assign the first two elements to different colors (R, B) and the rest to red (R)
    - This ensures the red set has a range of 0 (if all elements are the same) and blue has a non-zero range

Algorithms/Techniques:
    - Greedy approach
    - Array traversal

Time Complexity:
    O(n) per test case, where n is the length of the array
    We scan the array once to determine equality of first and last elements and then output the result

Space Complexity:
    O(1) - Constant extra space used, ignoring input/output

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    long y;
    for (long p = 1; p < n; p++) {
      scanf("%ld", &y);
    }
    if (x == y) {
      // All elements are the same, so no valid coloring possible
      puts("NO");
      continue;
    }
    // At least one element is different, so coloring is possible
    puts("YES");
    printf("RB");  // First two elements: Red, Blue
    for (long p = 2; p < n; p++) {
      printf("R");  // Remaining elements: Red
    }
    puts("");  // New line after outputting the coloring string
  }
}


// https://github.com/VaHiX/CodeForces/