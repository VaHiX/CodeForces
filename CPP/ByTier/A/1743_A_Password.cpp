/*
 * Problem URL : https://codeforces.com/problemset/problem/1743/A
 * Submit Date : 2025-08-21
 */

// LUOGU_RID: 91131735
#include <cstdio>
int T, n;
int main() {
  for (scanf("%d", &T); T--;)
    for (scanf("%d", &n), printf("%d\n", 3 * (10 - n) * (9 - n)); n--;)
      scanf("%*d");
}