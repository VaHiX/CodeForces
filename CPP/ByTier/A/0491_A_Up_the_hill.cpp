/*
 * Problem URL : https://codeforces.com/contest/491/problem/A
 * Submit Date : 2025-09-05
 */

/*
 * Problem URL : https://codeforces.com/contest/491/problem/A
 * Submit Date : 2025-09-02
 */



#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long up, down;
  scanf("%ld\n%ld", &up, &down);
  long N = up + down + 1;
  std::vector<long> height(N);
  for (int p = 0; p < N; p++) {
    height[p] = p + 1;
  }
  std::reverse(height.begin() + up, height.end());

  for (int p = 0; p < N; p++) {
    printf("%ld ", height[p]);
  }
  puts("");

  return 0;
}
