// Problem: CF 2106 D - Flower Boy
// https://codeforces.com/contest/2106/problem/D

/*
D. Flower Boy
Algorithms/Techniques: Two Pointers, Greedy, Preprocessing
Time Complexity: O(n + m) per test case
Space Complexity: O(n + m) per test case

The problem asks to find the minimum value k that Igor must place to ensure he can collect m flowers,
each with beauty at least b[i], using a greedy approach where we take as many flowers as possible in order.

We precompute for each position j (in b), what is the leftmost and rightmost flower in a that can be used
for collecting j-th flower. Then, if there's a way to select m flowers without adding anything,
we return 0. Otherwise, we try all positions where placing k could help, i.e., when l[i - 1] < r[i + 1],
and the minimum such k is the minimum of b[i].
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e5 + 10;
int t, n, m, ans;
int a[N], b[N];
int l[N], r[N];

void sovle() {
  cin >> n >> m;
  ans = 2e9;
  for (int i = 1; i <= m; i++)
    l[i] = 1e9, r[i] = 0;
  l[0] = 0, r[m + 1] = 1e9;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];

  // Find leftmost position for each required flower
  for (int i = 1, j = 1; i <= n && j <= m; i++)
    if (a[i] >= b[j])
      l[j] = i, j++;

  // Find rightmost position for each required flower
  for (int i = n, j = m; i >= 1 && j >= 1; i--)
    if (a[i] >= b[j])
      r[j] = i, j--;

  // Check whether it's already possible without inserting anything
  if (l[m] != 1e9 || r[1] != 0) {
    cout << 0 << "\n";
    return;
  }

  // Try all positions where we can insert one element to help construct valid sequence
  for (int i = 1; i <= m; i++) {
    if (l[i - 1] < r[i + 1])
      ans = min(ans, b[i]);
  }

  if (ans != 2e9)
    cout << ans << "\n";
  else
    cout << -1 << "\n";
  return;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    sovle();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/