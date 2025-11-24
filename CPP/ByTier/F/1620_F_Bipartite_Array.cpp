// Problem: CF 1620 F - Bipartite Array
// https://codeforces.com/contest/1620/problem/F

/*
 * Problem: Bipartite Array
 * 
 * Purpose: Given a permutation of integers from 1 to n, determine whether we can 
 *          construct a bipolar array where each element is either p[i] or -p[i].
 *          The resulting array must form a bipartite graph based on the specified 
 *          edge condition.
 * 
 * Algorithm: The solution uses dynamic programming with bitmasking and state tracking.
 *            We define states based on the parity of the current index and the value 
 *            assigned to the previous element to decide what value to assign to the
 *            current element such that the bipartite property holds.
 * 
 * Time Complexity: O(n^2) for each test case, due to nested loops over possible values.
 * Space Complexity: O(n) for auxiliary arrays used in DP.
 * 
 * Techniques: Dynamic Programming, Bitmasking, State Compression
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2e6 + 5;
int n, A[N], P[N], f[N];

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &A[i]);
  
  // Initialize arrays for dynamic programming
  for (int i = 1; i < 2 * n; ++i)
    P[i] = -1, f[i] = n + 1;  // Set initial values for tracking min/max states
  f[0] = f[1] = -n;  // Base cases for initial state

  // Perform DP step-by-step
  for (int i = 1; i < n; ++i)
    for (int x = 0; x < 2; ++x)    // Iterate through two possible parity choices
      for (int y = 0; y < 2; ++y) {   // Iterate through two possible sign choices
        int v[2] = {f[i * 2 - 2 + y], A[i - 1] * (2 * y - 1)};
        for (int j = 0; j < 2; ++j)
          if (v[j] <= A[i] * (2 * x - 1) && v[(j == 0)] < f[i * 2 + x])
            f[i * 2 + x] = v[!j], P[i * 2 + x] = i * 2 - 2 + y;
      }

  // Check if a valid solution exists
  if (f[2 * n - 1] <= n) {
    puts("YES");
    // Reconstruct the array using parent pointers
    for (int i = n - 1, x = 2 * n - 1; ~i; --i, x = P[x])
      if (x % 2 == 0)
        A[i] *= -1;
    // Output the result
    for (int i = 0; i < n; ++i)
      printf("%d ", A[i]);
    puts("");
  } else {
    puts("NO");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/