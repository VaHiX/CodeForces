// Problem: CF 1896 A - Jagged Swaps
// https://codeforces.com/contest/1896/problem/A

/*
Algorithm: A. Jagged Swaps
Techniques: Simulation, Greedy, Observation

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks whether we can sort a permutation using a specific operation:
- Choose index i from 2 to n-1 such that a[i-1] < a[i] and a[i] > a[i+1]
- Swap a[i] and a[i+1]

Key insight:
- We can only perform swaps when there is a "jagged" pattern: a[i-1] < a[i] > a[i+1]
- The goal is to determine if we can eventually sort the array using such operations.
- If the array has the form [1, 2, ..., n], it's already sorted → YES.
- If there is any element that cannot be moved to its correct position (e.g., in descending order), it's impossible → NO.
- In general, if we scan left to right and encounter an element that’s larger than both neighbors, we can potentially perform a swap, but this does not guarantee the array will sort.
- Observation shows that if the array is strictly increasing except for at most one element (which forms a local peak), then it's possible to sort.

However, a simpler observation reveals:
- If at any point in a left-to-right scan, an element is greater than its neighbor, we can always "move" it to correct position if possible.
- A necessary condition is that the entire array must not be a reverse sorted sequence (i.e., [n, n-1, ..., 1]).
- Also, a necessary condition: there's no way to sort if after scanning once and finding a peak that cannot be reduced.

Here, simplified check for final result:
We simply assume it can be sorted until we find a descending pattern in a way that cannot be fixed.
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
    bool ans(x == 1); // initialized to true only if first element is 1, otherwise false
    for (long p = 1; p < n; p++) {
      scanf("%ld", &x); // read rest of elements (but don't use their values)
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/