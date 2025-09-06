/*
 * Problem URL : https://codeforces.com/contest/609/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/609/problem/A
 * Submit Date : 2025-09-02
 */



#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {

  int n;
  scanf("%d\n", &n);
  long m;
  scanf("%ld\n", &m);

  std::vector<int> a(n);
  for (int p = 0; p < n; p++) {
    scanf("%d\n", &a[p]);
  }
  sort(a.begin(), a.end(), std::greater<int>());

  int count(0);
  while (m > 0) {
    m -= a[count++];
  }
  printf("%d\n", count);

  return 0;
}
