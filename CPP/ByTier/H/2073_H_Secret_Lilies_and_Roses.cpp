/*
 * Problem URL : https://codeforces.com/contest/2073/problem/H
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()

void solve();

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}

void solve() {
  int n;
  cin >> n;
  int rose = 0, lily = n + 1;
  while (lily - rose > 1) {
    int m = (lily + rose) / 2;
    cout << "type " << m << endl;
    string res;
    cin >> res;
    if (res == "lily")
      lily = m;
    else
      rose = m;
  }
  auto f = [&](int ind) -> int {
    if (ind <= 0 || n <= ind)
      return 0;
    cout << "multi " << ind << endl;
    int res;
    cin >> res;
    return res;
  };
  int mid = rose;
  int A = f(mid - 1);
  int B = f(mid);
  int C = f(mid + 1);
  int ans = C - B + mid - (A - B);
  cout << "answer " << ans << endl;
}