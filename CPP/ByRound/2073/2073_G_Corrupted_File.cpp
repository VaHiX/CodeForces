/*
 * Problem URL : https://codeforces.com/contest/2073/problem/G
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
#define max2(a, b) (a) > (b) ? (a) : (b)
#define ep 1e-7
#define mod 998244353
#define ll long long int
#define MAXN 300005
char a[100005];
char b[100005];
bool check(int n, int m) {
  int color = 0, len = 0;
  int cnt = 0;
  int p = 0;
  int f0 = 0, f1 = 0;
  int l = 0, last = -1;
  for (int i = 0; i < n; i++)
    f0 |= (a[i] == '0');
  for (int i = 0; i < m; i++)
    f1 |= (b[i] == '0');
  if (!f1 && f0)
    return false;
  for (int i = 0; i < n; i++) {
    if (l == m) {
      if (b[l - 1] == '0')
        break;
      if (a[i] == '0')
        l = last + 1;
      continue;
    }
    if (b[l] == '0') {
      last = l;
      if (a[i] == '0')
        l++;
    } else {
      if (a[i] == '0') {
        if (last != -1)
          l = last + 1;
        else
          break;
      } else
        l++;
    }
  }
  if (l == m)
    return true;
  else
    return false;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    cin >> a >> b;
    if (check(n, m)) {
      cout << "yes\n";
    } else {
      cout << "no\n";
    }
  }
}
