// Problem: CF 2035 D - Yet Another Real Number Problem
// https://codeforces.com/contest/2035/problem/D

/*
D. Yet Another Real Number Problem
Algorithms/Techniques: Stack-based approach with bit manipulation for efficient prefix processing.
Time Complexity: O(n * log(max(a[i]))) per test case due to bit operations and stack processing.
Space Complexity: O(n) for the arrays used in the solution.

Problem Summary:
For each prefix of array 'a', we compute the maximum possible sum after applying operations:
- If b[i] is even, we can divide it by 2 and multiply another element by 2.
We want to maximize the total sum of the transformed array.

The algorithm uses a stack-based approach with bit counting to efficiently manage how many
times each element's value is effectively halved (due to being divisible by powers of 2).
*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const int MAXN = 2e5 + 3, Mod = 1e9 + 7;
int T, n, top, a[MAXN], c[MAXN], stk[MAXN];
ll b[MAXN];

void Solve() {
  cin >> n, top = 0; // Initialize stack and input size
  ll ans = 0; // Final result for current prefix
  for (int i = 1; i <= n; i++) {
    cin >> a[i], b[i] = 1; // Read value, initialize base multiplier
    ll t = 1;
    c[i] = 0; // Count of divisions by 2 for current element
    
    // While stack not empty and top element's value allows merge
    for (; top && a[stk[top]] <= a[i] * (1ll << min(c[i], 30)); top--) {
      // Multiply the result with the previous b value, accumulate contribution to final answer
      (b[i] *= b[stk[top]]) %= Mod;
      c[i] += c[stk[top]]; // Add number of shifts from merged element
      
      // Subtract contribution of the popped element's previous value * multiplier
      (ans -= a[stk[top]] * (b[stk[top]] - 1)) %= Mod;
    }
    
    // Add contribution of current element with its multiplier
    (ans += a[i] * b[i] + Mod) %= Mod, stk[++top] = i;
    
    // Decompose the current element into power-of-2 components for further processing
    for (; a[i] % 2 == 0; a[i] >>= 1, b[i] <<= 1, c[i]++)
      ;
    b[i] %= Mod, cout << ans << " \n"[i == n]; // Output final answer and reset mod
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/