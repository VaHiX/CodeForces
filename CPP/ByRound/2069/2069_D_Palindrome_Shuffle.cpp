/*
 * Problem URL : https://codeforces.com/problemset/problem/2069/D
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t, cnt[200], l, r, ans, tot[200], x;
char s[300000];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    l = 1, r = n;
    for (int i = 'a'; i <= 'z'; i++)
      tot[i] = cnt[i] = 0;
    while (l < r && s[l] == s[r])
      l++, r--;
    for (int i = l; i <= r; i++)
      cnt[s[i]]++;
    x = l;
    for (int i = l; i <= r; i++) {
      tot[s[i]]++;
      if (i > n / 2) {
        if (s[i] != s[n - i + 1])
          break;
      } else {
        if (tot[s[i]] * 2 > cnt[s[i]])
          break;
      }
      x = i + 1;
    }
    ans = r - x + 1, x = r;
    for (int i = 'a'; i <= 'z'; i++)
      tot[i] = 0;
    for (int i = r; i >= l; i--) {
      tot[s[i]]++;
      if (i <= n / 2) {
        if (s[i] != s[n - i + 1])
          break;
      } else {
        if (tot[s[i]] * 2 > cnt[s[i]])
          break;
      }
      x = i - 1;
    }
    ans = min(ans, x - l + 1);
    printf("%d\n", ans);
  }
  return 0;
}