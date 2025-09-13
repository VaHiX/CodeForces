/*
 * Problem URL : https://codeforces.com/contest/2133/problem/D
 * Submit Date : 2025-08-30
 */

#include <iostream>
#define int long long
#define endl '\n'
using namespace std;
int ar[200005], d[200005];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> ar[i];
    d[1] = ar[1];
    for (int i = 2; i <= n; i++) {
      d[i] = min(d[i - 1] + ar[i] - 1,
                 d[i - 2] + ar[i - 1] + max(0ll, ar[i] - i + 1));
    }
    cout << d[n] << endl;
  }
  return 0;
}
