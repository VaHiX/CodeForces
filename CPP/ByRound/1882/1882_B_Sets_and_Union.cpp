// Problem: CF 1882 B - Sets and Union
// https://codeforces.com/contest/1882/problem/B

/*
B. Sets and Union
Algorithms/Techniques: Bit manipulation, greedy approach
Time Complexity: O(n * max_element) where max_element <= 50
Space Complexity: O(n)

The problem asks to find the maximum number of elements in a set that can be formed
by taking union of some subsets from given sets, such that this set is NOT equal
to the union of ALL given sets.

Approach:
1. For each bit position (from 1 to 50), we check if it's present in the total union.
2. If yes, we count how many subsets do NOT contain this bit.
3. We form a mask of all elements from such subsets and calculate popcount.
4. The maximum among all such counts is our answer.

*/

#include <stdint.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
#define LL long long
int T, n, k, x;
LL a[55], s; // a[i] stores the set as bitmask, s stores total union
int32_t main() {
  scanf("%d", &T);
  while (T--) {
    int mx = 0;
    s = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      a[i] = 0; // Clear the bitmask for current set
      scanf("%d", &k);
      while (k--) {
        scanf("%d", &x);
        a[i] |= 1ll << x; // Set the bit corresponding to element x
      }
      s |= a[i]; // Union all sets into s
    }
    for (int i = 1; i <= 50; i++)
      if (s >> i & 1) { // If bit i is set in total union
        LL tmp = 0;
        for (int j = 1; j <= n; j++)
          if (!(a[j] >> i & 1)) // If bit i is NOT set in subset j
            tmp |= a[j];       // Combine all elements from such subsets
        mx = max(mx, __builtin_popcountll(tmp)); // Count bits in tmp and update max
      }
    printf("%d\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/