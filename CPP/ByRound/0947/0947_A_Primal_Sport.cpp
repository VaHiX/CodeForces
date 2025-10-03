/*
 * Problem URL : https://codeforces.com/contest/947/problem/A
 * Submit Date : 2025-09-04
 */

#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1 << 20;
int d[N] = {0};

int main() {
  for (int i = 2; i < N; i++)
    if (d[i] <= 0)
      for (int j = i; j < N; j += i)
        d[j] = i;

  int n, ans = N;
  scanf("%d", &n);

  for (int i = n - d[n] + 1; i <= n; i++)
    if (i - d[i] >= 2)
      ans = min(ans, i - d[i] + 1);

  printf("%d\n", ans);
}
