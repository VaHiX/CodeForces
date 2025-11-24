// Problem: CF 2077 E - Another Folding Strip
// https://codeforces.com/contest/2077/problem/E

/*
E. Another Folding Strip
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

Algorithms/Techniques:
- Uses monotonic stack to compute contribution of each element in subarrays
- Computes the minimal number of operations to achieve a given configuration using folded strip logic
- Applies inclusion-exclusion principle with two passes over the data
- Efficient preprocessing using prefix sums and monotonic stacks for range queries

*/

#include <iostream>

using namespace std;
#define ll long long
const ll N = 200007, MOD = 998244353;
ll T, n, a[N], ans, stk[N], top, L[N], R[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  stk[0] = -1;
  while (T--) {
    cin >> n;
    ans = 0;
    // Prefix sum transformation: odd indices add previous, even indices subtract current from previous
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      if (i & 1)
        a[i] += a[i - 1];   // Odd index: add to prefix sum
      else
        a[i] = a[i - 1] - a[i]; // Even index: subtract current from prefix sum
    }
    
    // Initialize right boundaries
    for (int i = 1; i <= n; ++i)
      R[i] = n + 1;
    
    top = 0;
    // First pass with increasing stack to compute right boundaries
    for (int i = 1; i <= n; ++i) {
      while (top && a[stk[top]] < a[i])
        R[stk[top--]] = i;   // Pop elements smaller than current
      L[i] = stk[top];         // Left boundary is top of stack
      stk[++top] = i;          // Push current index
    }
    
    // Calculate contribution with positive sign
    for (int i = 1; i <= n; ++i)
      (ans += (R[i] - i) * (i - L[i]) % MOD * (a[i] % MOD)) %= MOD;
    
    top = 0;
    // Reset right boundaries
    for (int i = 1; i <= n; ++i)
      R[i] = n + 1;
    
    // Second pass with decreasing stack to compute right boundaries
    for (int i = 0; i <= n; ++i) {
      while (top && a[stk[top]] >= a[i])
        R[stk[top--]] = i;   // Pop elements greater or equal to current
      L[i] = stk[top];         // Left boundary
      stk[++top] = i;          // Push current index
    }
    
    // Calculate contribution with negative sign (inclusion-exclusion)
    for (int i = 1; i <= n; ++i)
      (ans -= (R[i] - i) * (i - L[i]) % MOD * (a[i] % MOD)) %= MOD;
    
    cout << (ans + MOD) % MOD << '\n'; // Ensure result is positive
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/