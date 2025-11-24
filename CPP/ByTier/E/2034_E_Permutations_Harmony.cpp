// Problem: CF 2034 E - Permutations Harmony
// https://codeforces.com/contest/2034/problem/E

/*
Code Purpose:
This code solves the problem of finding a k-harmonic set of permutations for given n and k.
A k-harmonic set means that the sum of elements at each index across all k permutations is constant.
The algorithm handles edge cases and constructs valid permutations when possible.

Algorithms/Techniques:
- Uses backtracking and permutation generation with next_permutation
- Special handling for k=1
- Precomputed factorials to optimize checking constraints
- Symmetry-based construction for odd k values

Time Complexity: O(k * n! * n) in worst case, where n! is for generating permutations and k is for constructing sets
Space Complexity: O(n) for storing temporary arrays and permutations

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 5e5 + 5;
int n, k, cc, a[N][3], fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40720};
void solve() {
  cc++;
  cin >> n >> k;
  if (k == 1) {
    if (n == 1)
      cout << "Yes\n1\n";
    else
      cout << "No\n";
    return;
  }
  if (n < 9 and (k > fact[n] or k == fact[n] - 1) or
      k % 2 == 1 and n % 2 == 0) {
    cout << "No\n";
    return;
  }
  vector<int> v;
  v.clear();
  cout << "Yes\n";
  for (int i = 1; i <= n; i++)
    a[i][0] = a[i][1] = a[2][i] = -1, v.push_back(i);
  if (k % 2 == 1) {
    for (int i = 1; i <= n; i++)
      a[i][0] = i;
    int ind = 1;
    for (int i = n / 2 + 2; i <= n; i++)
      a[ind++][1] = i;
    for (int i = 1; i < n / 2 + 2; i++)
      a[ind++][1] = i;
    for (int i = 1; i <= n; i++)
      a[i][2] = (3 * (n + 1)) / 2 - a[i][0] - a[i][1];
    for (int j = 0; j < 3; j++) {
      for (int i = 1; i <= n; i++)
        cout << a[i][j] << ' ';
      cout << '\n';
    }
    k -= 3;
  }
  do {
    if (k == 0)
      break;
    bool ok0 = 1, ok1 = 1, ok2 = 1;
    bool kk0 = 1, kk1 = 1, kk2 = 1;
    for (int i = 0; i < n; i++) {
      if (v[i] != a[i + 1][0])
        ok0 = 0;
      if (v[i] != a[i + 1][1])
        ok1 = 0;
      if (v[i] != a[i + 1][2])
        ok2 = 0;
    }
    for (int i = 0; i < n; i++) {
      if ((n + 1 - v[i]) != a[i + 1][0])
        kk0 = 0;
      if ((n + 1 - v[i]) != a[i + 1][1])
        kk1 = 0;
      if ((n + 1 - v[i]) != a[i + 1][2])
        kk2 = 0;
    }
    if (ok0 or kk0 or ok1 or kk1 or ok2 or kk2)
      continue;
    k -= 2;
    for (int i = 0; i < n; i++)
      cout << v[i] << ' ';
    cout << '\n';
    for (int i = 0; i < n; i++)
      cout << n + 1 - v[i] << ' ';
    cout << '\n';
  } while (next_permutation(v.begin(), v.end()));
  return;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/