// Problem: CF 1385 B - Restore the Permutation by Merger
// https://codeforces.com/contest/1385/problem/B

/*
B. Restore the Permutation by Merger
Algorithms/Techniques: Greedy
Time complexity: O(n) per test case
Space complexity: O(n)

The problem is about reconstructing a permutation from its merge with itself.
Key idea:
- We iterate through the merged array and for each element:
  - If it's already been seen (a[b] != 0), we skip it.
  - If it hasn't been seen, we print it (as part of the original permutation) and mark it as seen.
This works because in a merged permutation, every element appears twice,
but only the first occurrence in order gives us an element of the original permutation.
*/

#include <cstdio>
int t, n, a[57], i, b;
int main() {
  for (scanf("%d", &t); t--; puts(""))   // Read number of test cases and process each
    for (scanf("%d", &n), i = 0; i++ < 2 * n;)  // Read n and loop through 2*n elements
      scanf("%d", &b), a[b] ? a[b] = 0 : (printf("%d ", b), ++a[b]);  // Check if element seen, print if not, mark as seen
}


// https://github.com/VaHiX/codeForces/