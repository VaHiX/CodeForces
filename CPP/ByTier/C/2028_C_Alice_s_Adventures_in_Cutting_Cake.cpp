// Problem: CF 2028 C - Alice's Adventures in Cutting Cake
// https://codeforces.com/contest/2028/problem/C

/*
Algorithm/Techniques: Binary search on answer, prefix sums, two pointers
Time Complexity: O(n) per test case, where n is the number of sections in the cake.
Space Complexity: O(n) for storing prefix sums and auxiliary arrays.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
int T;
void work() {
  int n, m, v;
  cin >> n >> m >> v;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<ll> pre(n + 1); // Prefix sum array
  for (int i = 0; i < n; i++)
    pre[i + 1] = pre[i] + a[i];
  ll ans = -1;
  vector<int> f(m + 1), g(m + 1); // f[i] - minimum index to form i pieces from start; g[i] - maximum index to form i pieces from end

  // Precompute f[i]: smallest index such that we can make i pieces starting from 0
  for (int i = 1, j = 0; i <= m; i++) {
    while (j <= n && pre[j] - pre[f[i - 1]] < v)
      j++;
    f[i] = j;
  }

  // Precompute g[i]: largest index such that we can make i pieces ending at n
  g[0] = n;
  for (int i = 1, j = n; i <= m; i++) {
    while (j >= 0 && pre[g[i - 1]] - pre[j] < v)
      j--;
    g[i] = j;
  }

  // Try all valid combinations of pieces分配 to creatures
  for (int i = 0; i <= m; i++) {
    if (f[i] <= g[m - i]) {
      ans = max(ans, pre[g[m - i]] - pre[f[i]]);
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    work();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/