/*
 * Problem URL : https://codeforces.com/problemset/problem/2116/F
 * Submit Date : 2025-08-16
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long solve_one_case(int n, const vector<long long> &a,
                         const vector<long long> &b, const string &c) {
  long long base = 0;
  for (long long x : a) {
    base ^= x;
  }

  vector<long long> basis;
  for (int i = n - 1; i >= 0; i--) {
    long long v = a[i] ^ b[i];
    for (long long bv : basis) {
      if (v == 0)
        break;
      v = min(v, v ^ bv);
    }
    if (v != 0) {
      if (c[i] == '0') {
        base = min(base, base ^ v);
      } else {
        base = max(base, base ^ v);
      }
      basis.push_back(v);
    }
  }
  return base;
}

void solve() {
  int n;
  cin >> n;
  vector<long long> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  string c;
  cin >> c;

  long long ans = solve_one_case(n, a, b, c);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}