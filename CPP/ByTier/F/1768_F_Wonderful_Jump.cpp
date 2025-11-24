// Problem: CF 1768 F - Wonderful Jump
// https://codeforces.com/contest/1768/problem/F

/*
Flowerbox: 
Problem: F. Wonderful Jump
Purpose: Find the minimum cost (eris) to reach each index from index 1 in an array, where the cost of a jump from index i to j is min(a[i], a[i+1], ..., a[j]) * (j - i)^2.
Algorithms/Techniques:
  - Dynamic Programming with pruning
  - For each index i, we look backwards and forwards within a limited range
  - Optimization: If an element in the path is smaller than or equal to the current element, we can break early since the cost will only increase.
Time Complexity: O(n^2) in worst case, but optimized by pruning. In practice, much better due to early breaks.
Space Complexity: O(n) for the DP array and input array.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

#define int long long
using namespace std;
int a[400010], f[400010]; // a: input array, f: DP array storing min cost to reach each index
signed main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%lld", a + i), f[i] = (int)(1e18 + 3); // Initialize f with large value
  f[1] = 0; // Starting point cost is 0
  for (int i = 1; i <= n; i++) {
    // Look backwards from i to find valid previous positions
    for (int j = i - 1; j > 0 && j >= i - n / a[i]; j--) {
      f[i] = min(f[i], f[j] + a[i] * (i - j) * (i - j)); // Update cost to reach i
      if (a[j] <= a[i]) // Optimization: if we can't improve further, stop
        break;
    }
    // Look forwards from i to find valid next positions
    for (int j = i + 1; j <= n && j <= i + n / a[i]; j++) {
      f[j] = min(f[j], f[i] + a[i] * (i - j) * (i - j)); // Update cost to reach j
      if (a[j] <= a[i]) // Optimization: if we can't improve further, stop
        break;
    }
  }
  for (int i = 1; i <= n; i++)
    printf("%lld ", f[i]); // Output result
}


// https://github.com/VaHiX/CodeForces/