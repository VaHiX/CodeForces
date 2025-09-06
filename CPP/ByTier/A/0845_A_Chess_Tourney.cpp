/*
 * Problem URL : https://codeforces.com/contest/845/problem/A
 * Submit Date : 2025-09-01
 */

/*
 * Problem URL : https://codeforces.com/contest/845/problem/A
 * Submit Date : 2025-08-31
 */



#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(2 * n);
  for (long p = 0; p < 2 * n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  puts(a[n - 1] < a[n] ? "YES" : "NO");

  return 0;
}
