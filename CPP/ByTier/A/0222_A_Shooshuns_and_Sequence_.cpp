/*
 * Problem URL : https://codeforces.com/problemset/problem/222/A
 * Submit Date : 2025-08-09
 */

#include <cstdio>

using namespace std;

int main() {
  int n, k, a, last(0), continuous(1);
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a);
    if (a == last) {
      continuous += 1;
    } else {
      continuous = 1;
    }
    last = a;
  }
  printf("%d\n", continuous + k > n ? n - continuous : -1);
  return 0;
}
