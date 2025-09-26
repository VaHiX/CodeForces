/*
 * Problem URL : https://codeforces.com/contest/1646/problem/B
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);
  printf(accumulate(a, a + (n + 1) / 2, 0ll) <
                 accumulate(a + (n + 2) / 2, a + n, 0ll)
             ? "YES\n"
             : "NO\n");
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i) {
    solve();
  }
}