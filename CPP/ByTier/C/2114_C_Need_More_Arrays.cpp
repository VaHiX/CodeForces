// Problem: CF 2114 C - Need More Arrays
// https://codeforces.com/contest/2114/problem/C

/*
C. Need More Arrays
Algorithm: Greedy approach to maximize number of arrays by selectively removing elements.
Approach:
- Traverse the array from left to right.
- For each element, decide whether to start a new array or continue the current one based on:
  if (prev + 1 < x), then start a new array and increment count.
- This ensures that consecutive elements that are not in sequence are placed in separate arrays.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1) - only using a few variables regardless of input size.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    long cnt(1); // Start with one array
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (prev + 1 < x) { // If current element breaks the sequence
        ++cnt;           // Start a new array
        prev = x;        // Update previous to current element
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/