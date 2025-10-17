/*
 * Problem URL : https://codeforces.com/contest/301/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
int n, ans, k, t = 1e5;
int main() {
  scanf("%d", &n);
  for (int i = 1, x; i <= n * 2 - 1; i++)
    scanf("%d", &x), ans += abs(x), k += x < 0, t = std::min(t, abs(x));
  printf("%d", (n & 1 || !(n & 1) && !(k & 1)) ? ans : ans - 2 * t);
}
