// Problem: CF 1575 L - Longest Array Deconstruction
// https://codeforces.com/contest/1575/problem/L

/* 
L. Longest Array Deconstruction
Algorithms/Techniques: Sorting, Binary Search, Greedy + LIS-like approach
Time Complexity: O(n log n)
Space Complexity: O(n)

Problem Description:
Given a sequence a of length n, we want to maximize the number of indices i such that a[i] == i.
We can remove elements from the array and concatenate the remaining parts. 
This problem is solved by finding the longest subsequence where for each element a[i], 1-based index >= a[i]
which can be reduced to a variant of Longest Increasing Subsequence (LIS).

The approach:
- For each element a[i], create a pair (a[i], -i), and sort these pairs.
- Use binary search with a dynamic array 'c' to maintain the smallest tail of increasing subsequence lengths.
- The key insight is that for an element with value v at position p, if p >= v, then it can be part of valid sequence.
- This allows us to greedily build the longest possible such subsequence using LIS technique.

*/
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;
int a[200002], c[200002], i, n, d, x, y;
pair<int, int> b[200002];
int main() {
  scanf("%d", &n); // Read the number of elements
  for (i = 1; i <= n; i = i + 1) {
    scanf("%d", &a[i]); // Read each element of array
    b[i] = pair<int, int>(a[i], -i); // Create pairs of (value, -index)
  }
  sort(b + 1, b + n + 1); // Sort the pairs by value, then by index (negative for descending order)
  for (i = 1; i <= n; i = i + 1)
    if (-b[i].second >= b[i].first) { // Check if position >= value
      x = -b[i].second - b[i].first; // Compute offset
      d = upper_bound(c + 1, c + y + 1, x) - c; // Binary search for insertion point
      c[d] = x; // Place the offset in the array
      y = max(y, d); // Update maximum length found so far
    }
  printf("%d", y); // Output the result (maximum length of valid subsequence)
  return 0;
}


// https://github.com/VaHiX/codeForces/