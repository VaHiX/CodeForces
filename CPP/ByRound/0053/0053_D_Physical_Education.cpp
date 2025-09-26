/*
 * Problem URL : https://codeforces.com/problemset/problem/53/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
#define maxn 300

int a[maxn], b[maxn];
vector<int> ret;

int main() {
  int n, i, k, h, cnt = 0;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", a + i);
  for (i = 0; i < n; i++)
    scanf("%d", b + i);
  for (i = 0; i < n; i++)
    if (b[i] != a[i]) {
      for (k = i + 1; k < n; k++)
        if (b[k] == a[i]) {
          for (h = k; h > i; h--) {
            b[h] = b[h - 1];
            ret.push_back(h);
          }
          break;
        }
    }
  printf("%zu", ret.size());
  for (i = 0; i < ret.size(); i++)
    printf("\n%d %d", ret[i], ret[i] + 1);
  return 0;
}