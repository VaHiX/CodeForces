// Problem: CF 1852 A - Ntarsis' Set
// https://codeforces.com/contest/1852/problem/A

/*
Algorithm: Ntarsis' Set
Techniques: Two-pointer technique, simulation with optimized index tracking

Time Complexity: O(n + k)
Space Complexity: O(n)

The problem simulates removing elements from a sorted set S = {1, 2, ..., 10^1000} based on the indices in array `a`.
Each day, we remove the a[1]-th, a[2]-th, ..., a[n]-th smallest numbers in S.
We are to find the smallest number remaining after k such days.

This implementation tracks how many elements have been removed via an iterative process using two pointers.
The key idea is to precompute the next valid element in the sequence as we simulate removals:
- `nw` represents the current pointer or offset in the sequence.
- `j` tracks how far we can go before we hit a point where a[j+1] - j <= nw.
- We increment `j` as long as it's safe to remove elements up to that point.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 5;
int T, n, k, a[N], s[N];

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    long long nw = 1; // Starting position in the sequence
    for (int i = 1, j = 0; i <= k; ++i) {
      // Move j forward while it's safe to remove elements up to current value
      while (j < n && a[j + 1] - j <= nw)
        ++j;
      nw += j; // Update the next position based on how many were removed
    }
    printf("%lld\n", nw);
  }
}


// https://github.com/VaHiX/codeForces/