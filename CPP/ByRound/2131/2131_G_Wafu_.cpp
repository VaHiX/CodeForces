/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/G
 * Submit Date : 2025-08-14
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#define M 200000
#define ll long long
#define MAXX 200500
#define mod 1000000007
using namespace std;
ll dp[31];
int a[MAXX];
int main() {
  // freopen("G.in","r",stdin);
  ios::sync_with_stdio(false);
  for (int i = 1; i <= 30; i++) {
    dp[i] = i;
    for (int j = 1; j < i; j++)
      dp[i] = dp[i] * dp[j] % mod;
  }
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1);
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
      if (a[i] > 30 || (1 << (a[i] - 1)) > k) {
        if (k) {
          ans = ans * a[i] % mod;
          k--;
          for (int j = 1; j <= 30; j++) {
            if (k & (1 << (j - 1))) {
              ans = ans * dp[j] % mod;
            }
          }
        }
        break;
      } else {
        k -= (1 << (a[i] - 1));
        ans = ans * dp[a[i]] % mod;
      }
    }
    cout << ans << endl;
  }
  return 0;
}