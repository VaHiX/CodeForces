// Problem: CF 2151 D - Grid Counting
// https://codeforces.com/contest/2151/problem/D

/*
D. Grid Counting
Algorithms/Techniques: Difference array, Fast exponentiation, Combinatorics
Time Complexity: O(n * log n) per test case
Space Complexity: O(n)

This problem involves counting the number of valid ways to color cells in an n×n grid such that:
1. Each row k has exactly a[k] black cells.
2. There exists exactly one cell with max(x_i, y_i) = k for each k.
3. There exists exactly one cell with max(x_i, n+1-y_i) = k for each k.

The solution uses difference arrays to track constraints and combinatorics to compute the result efficiently.
*/

#include <iostream>

using namespace std;
const int M = 998244353;
int a[200010];
long long ms[200010], cs[200010];
long long ans;

inline void work() {
  int n;
  cin >> n;
  ans = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ms[i] = 0;
    cs[i] = 0;
  }
  ms[0] = 0, cs[0] = 0;
  int have = 0;
  for (int i = n; i >= 1; i--) {
    if (2 * i <= n)
      have += 2;
    else {
      if (i * 2 == n + 1)
        have++;
    }
    if (have < a[i]) {
      cout << "0\n";
      return;
    }
    ms[have - a[i] + 1]++; // Mark start of interval
    ms[have + 1]--;        // Mark end of interval
    cs[1]++;               // Start of contribution interval
    cs[a[i] + 1]--;        // End of contribution interval
    have -= a[i];          // Update available slots
  }
  if (have > 0) {
    cout << "0\n";
    return;
  }
  for (int i = 1; i <= n; i++) {
    ms[i] += ms[i - 1];    // Compute prefix sum of intervals
    cs[i] += cs[i - 1];    // Compute prefix sum of intervals
    long long c = ms[i], cf = i;
    while (c) {
      if (c % 2)
        ans = ans * cf % M; // Multiply by power of cf using binary exponentiation
      cf = cf * cf % M;
      c /= 2;
    }
    c = M - 2, cf = i;
    long long tcf = 1;
    while (c) {
      if (c % 2)
        tcf = tcf * cf % M; // Modular inverse of cf
      cf = cf * cf % M;
      c /= 2;
    }
    c = cs[i], cf = tcf;
    while (c) {
      if (c % 2)
        ans = ans * cf % M; // Final multiplication with modular inverse
      cf = cf * cf % M;
      c /= 2;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/