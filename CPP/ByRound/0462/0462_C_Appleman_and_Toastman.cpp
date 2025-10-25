/*
 * Problem URL : https://codeforces.com/contest/462/problem/C
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <stdio.h>
using namespace std;
long long S, w[301000];
int main() {
  int i, n;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
  }
  sort(w + 1, w + n + 1);
  for (i = 1; i <= n; i++) {
    S += min(n, i + 1) * w[i];
  }
  printf("%lld\n", S);
}
