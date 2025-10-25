// Problem: CF 2112 B - Shrinking Array
// https://codeforces.com/contest/2112/problem/B

/*
B. Shrinking Array

Purpose:
This program determines the minimum number of operations required to make an array "beautiful".
An array is considered beautiful if it has at least two elements and there exists a position i such that |b[i] - b[i+1]| <= 1.
Each operation allows selecting two adjacent elements, choosing a value x between them (inclusive), and replacing them with x.

Algorithms/Techniques:
- Greedy approach with linear scanning
- Simulation of array operations with early termination logic

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1), only using a constant amount of extra space.

Input Format:
- First line contains number of test cases t
- For each test case:
  - First line: n (size of array)
  - Second line: n integers representing the array

Output Format:
- For each test case, output minimum operations required to make array beautiful, or -1 if impossible.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long pprev;          // Previous previous element
    scanf("%ld", &pprev);
    long prev;           // Previous element
    scanf("%ld", &prev);
    int ans =               // Answer variable: 0 if already beautiful, 1 for one op needed, -1 if impossible
        (prev == pprev || prev == pprev + 1 || prev == pprev - 1) ? 0 : -1;
    for (long p = 2; p < n; p++) {
      long x;            // Current element
      scanf("%ld", &x);
      if (ans < 0) {     // If we haven't determined a valid case yet
        // Check for local maximum or minimum that could lead to beauty
        if (pprev < prev && prev > x) {
          ans = 1;       // Found a peak that could be resolved with one operation
        } else if (pprev > prev && prev < x) {
          ans = 1;       // Found a valley that could be resolved with one operation
        }
      }
      if (ans) {         // If we have already started considering a solution
        // Check conditions to maintain beauty after current operation
        if (pprev == prev || prev == x) {
          ans = 0;       // Adjacent elements equal, array is beautiful
        } else if (prev == pprev - 1 || prev == pprev + 1) {
          ans = 0;       // Elements form a consecutive sequence, array is beautiful
        } else if (prev == x - 1 || prev == x + 1) {
          ans = 0;       // Adjacent elements are one apart, array is beautiful
        }
      }
      pprev = prev;      // Move window forward
      prev = x;
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/