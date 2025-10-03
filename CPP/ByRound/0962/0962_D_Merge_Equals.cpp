/*
 * Problem URL : https://codeforces.com/contest/962/problem/D
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<ll, int> mp;
ll a[1000010], vis[1000001];
int main(int argc, char const *argv[]) {
  int n, cnt = 0;
  ;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    while (mp[a[i]]) {
      int pre = mp[a[i]];
      mp[a[i]] = 0;
      vis[pre] = 1;
      cnt--;
      a[i] = a[i] << 1;
    }
    mp[a[i]] = i;
  }
  printf("%d\n", n + cnt);
  for (int i = 1; i <= n; i++)
    if (vis[i] == 0)
      printf("%lld ", a[i]);
  return 0;
}
