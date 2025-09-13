/*
 * Problem URL : https://codeforces.com/contest/2133/problem/A
 * Submit Date : 2025-08-30
 */

#include <cstdio>
#include <iostream>
using namespace std;
int vis[110];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 100; i++)
      vis[i] = 0;
    int ans = 0;
    while (n--) {
      int opt;
      scanf("%d", &opt);
      ans += vis[opt];
      vis[opt]++;
    }
    printf("%s\n", ans > 0 ? "YES" : "NO");
  }
}