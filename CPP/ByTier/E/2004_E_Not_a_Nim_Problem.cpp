/*
 * Problem URL : https://codeforces.com/contest/2004/problem/E
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 10000010;

int grundy[N];
bitset<N> vis;

int main() {
  grundy[1] = 1;
  for (int i = 3, at = 1; i < N; i += 2)
    if (!vis[i]) {
      ++at;
      for (int j = i; j < N; j += 2 * i)
        if (!vis[j])
          vis[j] = 1, grundy[j] = at;
    }
  int t;
  cin >> t;
  while (t--) {
    int n;
    scanf("%d", &n);
    int sum = 0;
    while (n--) {
      int x;
      scanf("%d", &x);
      sum ^= grundy[x];
    }
    puts(sum ? "Alice" : "Bob");
  }
  return 0;
}
