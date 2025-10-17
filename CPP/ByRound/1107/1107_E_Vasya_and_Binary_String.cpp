/*
 * Problem URL : https://codeforces.com/problemset/problem/1107/E
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
int n, a[200];
char s[200];
long long f[200][200][200];
long long solve(int l, int r, int pre) {
  if (l > r)
    return 0;
  if (l == r)
    return a[pre];
  long long &ans = f[l][r][pre];
  if (ans)
    return ans;
  ans = a[pre] + solve(l + 1, r, 1);
  for (int i = l + 1; i <= r; i++)
    if (s[l] == s[i])
      ans = max(ans, solve(l + 1, i - 1, 1) + solve(i, r, pre + 1));
  return ans;
}
int main() {
  cin >> n;
  cin >> s + 1;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cout << solve(1, n, 1) << endl;
  return 0;
}