// Problem: CF 2023 B - Skipping
// https://codeforces.com/contest/2023/problem/B

// Problem: B. Skipping
// Purpose: Maximize points in a problem-solving olympiad with specific skipping rules.
// Algorithm: Dynamic Programming with Binary Indexed Tree (Fenwick Tree)
// Time Complexity: O(n log n) per test case
// Space Complexity: O(n)

#include <algorithm>
#include <iostream>

#define ll long long
using namespace std;
const int N = 4e5 + 5;
int T, n, b[N];
ll a[N], f[N], s[N];

// Update BIT to keep minimum value at position u
void add(int u, ll v) {
  while (u)
    s[u] = min(s[u], v), u -= u & -u; // Update all ancestors in BIT
}

// Query BIT for minimum value from u to n
ll ask(int u) {
  ll res = 1e18;
  while (u <= n)
    res = min(res, s[u]), u += u & -u; // Query all relevant nodes
  return res;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n, fill(f, f + 1 + n, 1e18), fill(s, s + 1 + n, 1e18); // Initialize arrays
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i];
    add(1, 0); // Starting point: initial cost is 0
    ll ans = 0, sum = 0;
    for (int i = 1; i <= n; i++)
      f[i] = ask(i), add(b[i], f[i] + a[i]); // DP transition using BIT
    for (int i = 1; i <= n; i++)
      sum += a[i], ans = max(ans, sum - f[i]); // Calculate best score
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/codeForces/