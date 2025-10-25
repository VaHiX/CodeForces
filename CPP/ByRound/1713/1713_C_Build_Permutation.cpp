// Problem: CF 1713 C - Build Permutation
// https://codeforces.com/contest/1713/problem/C

/*
C. Build Permutation
Algorithm: Construct a permutation such that for each index i, a[i] + i is a perfect square.
Time Complexity: O(n * sqrt(n)) per test case, due to nested loop structure and sqrt computation.
Space Complexity: O(n) for storing the array a[].

Approach:
- For each n, we build a permutation where a[i] + i is a perfect square.
- We process numbers in reverse order, assigning values based on perfect squares.
- The algorithm uses a greedy-like method to construct the valid permutation by working backwards.
*/

#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;
int t, n, a[200005], m, p;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    m = n;
    a[0] = 0;
    while (n > 1) {
      p = sqrt(n); // Find the integer square root of current n
      if (p * p < n - 1)
        p++; // Adjust p to ensure p*p >= n-1
      for (int i = n - 1; p * p - i < n; i--) // Fill array from n-1 down to p*p-n+1
        a[i] = p * p - i;
      n = p * p - n + 1; // Update n to the next segment size
    }
    for (int i = 0; i < m; i++)
      printf("%d ", a[i]);
    printf("\n");
  }
}


// https://github.com/VaHiX/codeForces/