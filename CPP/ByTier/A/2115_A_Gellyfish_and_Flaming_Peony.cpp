// Problem: CF 2115 A - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2115/problem/A

/*
Problem: A. Gellyfish and Flaming Peony
Algorithm: Dynamic Programming with GCD preprocessing
Time Complexity: O(N^2 * log(max_value) + N * max_value)
Space Complexity: O(N * max_value)

Approach:
- Precompute all GCD values for numbers up to 5000.
- For each test case, find the minimum operations required to make all elements equal.
- The key idea is that we can only reduce elements using GCD operations,
  and the final answer will be related to how many times we need to update
  the array to reach a uniform value.

Steps:
1. Precompute GCD for all pairs from 1 to 5000.
2. Read input array and compute global GCD (d) and maximum element (p).
3. Check if any element equals d.
4. Use DP: dp[i] = minimum operations to reduce all elements to gcd(i, some existing element)
5. Return the best result from DP.

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 5e3 + 5;
int t, n, a[N], dp[N], _gcd[N][N];

void min(int &x, int y) {
  if (x > y)
    x = y;
}

int main() {
  // Precompute GCD for all pairs from 1 to 5000
  for (int i = 0; i <= 5000; i++)
    _gcd[i][0] = _gcd[0][i] = _gcd[i][i] = i;
  for (int i = 1; i <= 5000; i++)
    for (int j = 1; j < i; j++) {
      _gcd[i][j] = _gcd[j][i] = _gcd[j][i % j]; // Euclidean GCD
    }

  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int d = 0, p = 0, cnt = 0;
    
    // Read array elements and compute global GCD (d), max value (p)
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), d = _gcd[d][a[i]], p = max(p, a[i]);

    // Count how many elements already equal to the global GCD
    for (int i = 1; i <= n; i++)
      cnt += (a[i] == d);
    
    // If any element is already equal to the global GCD, we can minimize operations
    if (cnt) {
      printf("%d\n", n - cnt);
      continue;
    }

    // Initialize dp array: dp[i] = minimum operations to get value i
    for (int i = 1; i <= p; i++)
      dp[i] = n + 1;

    // Dynamic Programming step
    for (int i = 1; i <= n; i++) {
      // For every previous state, update with current element's GCD results
      for (int j = 1; j <= p; j++)
        min(dp[_gcd[j][a[i]]], dp[j] + 1);
      
      // Reset dp[a[i]] to 0 (no operation needed if we already have this element)
      dp[a[i]] = 0;
    }

    // Print final result: best way to reach the global GCD
    printf("%d\n", dp[d] + n - 1);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/