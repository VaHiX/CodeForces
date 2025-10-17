/*
 * Problem URL : https://codeforces.com/contest/871/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
#define bupol __builtin_popcount
#define ll long long
#define fi first
#define se second
#define pb push_back
using namespace std;
const ll MAXN = 2e5 + 10;
const int MAXS = 1e6 + 10;
const int INF = 1e9 + 10;
const ll MOD = 998244353;
const ll LOG = 30;
typedef pair<int, int> pii;
typedef pair<pii, ll> ipii;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    if (n == 1 || n == 2 || n == 3 || n == 5 || n == 7 || n == 11)
      cout << -1;
    else if (n % 4 == 1 || n % 4 == 3)
      cout << n / 4 - 1;
    else
      cout << n / 4;

    cout << '\n';
  }
}