/*
 * Problem URL : https://codeforces.com/contest/1379/problem/A
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, f, h, i;
char r[64], s[64], z[] = "abacaba";
int main() {
  for (scanf("%d", &t); t--;
       f == 1 ? printf("Yes\n%s\n", r) : printf("No\n"), f = 0)
    for (scanf("%d%s", &n, s), r[n] = 0, n = 6; s[n] && f != 1; ++n) {
      for (h = 1, i = 0; i != 7;
           h &= s[n - i] == (r[n - i] = z[i]) || s[n - i] == '?', ++i)
        ;
      for (i = 0; h && s[i];
           i + 6 < n || n < i ? r[i] = (s[i] == '?' ? 'z' : s[i]) : 0, ++i)
        ;
      for (f = i = 0; h && s[i]; f += !strncmp(r + i, z, 7), ++i)
        ;
    }
  return 0;
}