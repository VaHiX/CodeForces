/*
 * Problem URL : https://codeforces.com/problemset/problem/2070/D
 * Submit Date : 2025-08-23
 */

#include <iostream>
#include <vector>
using namespace std;
const long long M = 998244353;
void solve(int n, vector<int> &p) {
  vector<int> d(n + 1, 0);
  for (int i = 2; i <= n; i++)
    d[i] = d[p[i - 2]] + 1;
  int m = 0;
  for (int i = 2; i <= n; i++)
    m = max(m, d[i]);
  vector<long long> a(m + 1, 0);
  for (int i = 2; i <= n; i++)
    a[d[i]]++;
  vector<long long> s(m + 1, 0);
  s[m] = a[m] % M;
  for (int i = m - 1; i >= 1; i--)
    s[i] = (a[i] + (a[i] - 1 + M) % M * s[i + 1]) % M;
  cout << (1 + s[1]) % M << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> p(n - 1);
    for (int &i : p)
      cin >> i;
    solve(n, p);
  }
  return 0;
}
