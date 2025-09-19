/*
 * Problem URL : https://codeforces.com/contest/2026/problem/C
 * Submit Date : 2025-09-10
 */

#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 4e5 + 10;
int t, n;
char s[N];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%s", &n, s + 1);
    long long ans = 0;
    for (int i = n, j = 0; j < i; i--)
      if (s[i] == '0')
        ans += i - j, j = max(j - 1, 0);
      else
        ans += ++j;
    printf("%lld\n", ans);
  }
  return 0;
}