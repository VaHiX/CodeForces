/*
 * Problem URL : https://codeforces.com/problemset/problem/248/A
 * Submit Date : 2025-08-09
 */

#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
  int n, l, r, left(0), right(0);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &l, &r);
    left += l;
    right += r;
  }
  printf("%d\n", min(left, n - left) + min(right, n - right));
  return 0;
}
