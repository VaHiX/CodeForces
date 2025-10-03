/*
 * Problem URL : https://codeforces.com/contest/398/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

int r, b;

long long solve(int k) {
  long long ans = 1LL * (r - k + 1) * (r - k + 1) + k - 1;
  ans -= 1LL * (k + 1) * (b / (k + 1)) * (b / (k + 1));
  ans -= 1LL * (b % (k + 1)) * (b / (k + 1) * 2 + 1);
  return ans;
}

int main() {
  ios_base ::sync_with_stdio(false), cin.tie(0), cout.tie(0);

  cin >> r >> b;
  if (!r) {
    cout << -1LL * b * b << endl;
    cout << string(b, 'x') << endl;
    return 0;
  }

  int ans = 1;
  for (int i = 1; i <= r; i++)
    if (solve(i) > solve(ans))
      ans = i;

  cout << solve(ans) << endl;
  for (int i = 0; i < ans; i++) {
    cout << string(b / (ans + 1), 'x');
    if (b % (ans + 1))
      cout << 'x', b--;
    cout << 'o';
  }
  cout << string(r - ans, 'o') << string(b / (ans + 1), 'x') << endl;
}
