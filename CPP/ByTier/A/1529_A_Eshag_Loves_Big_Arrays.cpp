// Problem: CF 1529 A - Eshag Loves Big Arrays
// https://codeforces.com/contest/1529/problem/A

/*
A. Eshag Loves Big Arrays
Algorithms/Techniques: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to find the maximum number of elements that can be deleted from an array by repeatedly choosing a subsequence,
and deleting all elements in that subsequence which are strictly greater than the average of the subsequence.

Key insight:
- To maximize deletions, we should always choose a subsequence that includes the minimum element and possibly others.
- When we pick a subsequence, any elements larger than the average get deleted.
- If all elements are equal, no deletion is possible.
- Otherwise, by repeatedly removing elements greater than the current average, eventually only elements equal to the minimum value remain.
- The answer is simply the total number of elements minus the count of minimum elements,
  since those minimum elements cannot be deleted.

Code Logic:
- For each test case, read n and the array of n integers.
- Find the minimum element in the array.
- Count how many times this minimum element appears.
- Output n - cnt (number of non-minimum elements that can be deleted).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long min(107), cnt(0); // Initialize min to a large value, cnt counts occurrences of minimum
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < min) { // Found a new smaller element, update min and reset count
        min = x;
        cnt = 1;
      } else if (x == min) { // Increment count if element equals current minimum
        ++cnt;
      }
    }
    printf("%ld\n", n - cnt); // Number of elements that can be deleted
  }
}


// https://github.com/VaHiX/codeForces/