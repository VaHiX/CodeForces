// Problem: CF 1778 B - The Forbidden Permutation
// https://codeforces.com/contest/1778/problem/B

/*
Purpose: 
This code solves the problem of finding the minimum number of adjacent swaps needed to make a given subsequence of a permutation "good". A subsequence is considered good if for every consecutive pair in the subsequence, the position of the second element in the permutation is either less than the position of the first element or greater than the first element plus d.

Algorithms/Techniques:
- Position mapping: For each element in the permutation, store its index.
- Greedy approach: Calculate the minimum adjacent swaps needed by checking constraints between consecutive elements in the mapped positions.

Time Complexity: O(n + m) per test case, where n is the length of the permutation and m is the length of the array a.
Space Complexity: O(n + m), for storing the permutation indices and the array a.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
int p[100500]; // Stores the position of each element in the permutation
int a[100500]; // Stores the positions of elements of array a in the permutation
int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 0; tt < t; tt++) {
    int n, m, d;
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 0; i < n; i++) {
      int pp;
      scanf("%d", &pp);
      p[pp - 1] = i; // Map each element to its index in the permutation (0-based)
    }
    for (int i = 0; i < m; i++) {
      int aa;
      scanf("%d", &aa);
      a[i] = p[aa - 1]; // Map each element of array a to its index in the permutation
    }
    int ans = n - 1; // Initialize answer with maximum possible swaps
    for (int i = 1; i < m; i++) {
      // Check if the current pair violates the "good" condition
      if (a[i] < a[i - 1] || a[i] > a[i - 1] + d) {
        ans = 0; // If so, no more swaps are needed because array is already good
        break;
      }
      int dd = a[i] - a[i - 1]; // Calculate the gap between consecutive elements
      ans = min(ans, dd); // Update minimum swaps based on the gap
      if (d + 2 <= n) // Check for an additional constraint involving d
        ans = min(ans, d - dd + 1); // Consider the symmetric case for minimum swaps
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/