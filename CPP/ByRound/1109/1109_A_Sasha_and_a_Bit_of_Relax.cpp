/*
 * Problem URL : https://codeforces.com/contest/1109/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
#define maxn (1 << 20)
#define LL long long
using namespace std;

int n, f[maxn][2];

int main() {
  scanf("%d", &n);
  LL ans = 0;
  f[0][0]++;
  for (int i = 1, sum = 0; i <= n; i++) {
    int a;
    scanf("%d", &a);
    ans += f[sum ^= a][i & 1]++;
  }
  printf("%I64d\n", ans);
}