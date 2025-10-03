/*
 * Problem URL : https://codeforces.com/contest/1586/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
int T, n, sum, a[110], flag;
int isPrime(int x) {
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0)
      return 0;
  return 1;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    sum = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), sum += a[i];
    flag = isPrime(sum);
    printf("%d\n", n - flag);
    for (int i = 1; i <= n; i++) {
      if (flag && a[i] % 2 == 1)
        flag = 0;
      else
        printf("%d ", i);
    }
    printf("\n");
  }
  return 0;
}
