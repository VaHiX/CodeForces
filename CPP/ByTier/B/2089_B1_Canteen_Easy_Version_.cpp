/*
 * Problem URL : https://codeforces.com/problemset/problem/2089/B1
 * Submit Date : 2025-08-22
 */

#include <iostream>
#include <stack>
#define int long long
#define endl '\n'
using namespace std;
int ar[400005];
stack<int> s;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, x, ans = 0, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
      cin >> ar[i];
    for (int j = 1; j <= n; j++)
      cin >> x, ar[j] -= x;
    for (int i = 1; i <= n; i++)
      ar[i + n] = ar[i];
    for (int i = 1; i <= 2 * n; i++)
      ar[i] += ar[i - 1];
    for (int i = n * 2; i >= 1; i--) {
      while (!s.empty() && ar[s.top()] > ar[i])
        s.pop();
      if (!s.empty() && i <= n)
        ans = max(s.top() - i, ans);
      s.push(i);
    }
    cout << ans << endl;
    while (!s.empty())
      s.pop();
  }
  return 0;
}
