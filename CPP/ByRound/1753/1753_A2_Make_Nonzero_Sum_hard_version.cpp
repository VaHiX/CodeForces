// Problem: CF 1753 A2 - Make Nonzero Sum (hard version)
// https://codeforces.com/contest/1753/problem/A2

/*
Algorithm: Greedy
Time Complexity: O(n) where n is the length of the array
Space Complexity: O(n) for storing the array and auxiliary arrays

This solution works by trying to balance the alternating sums of segments.
The key insight is that we can make segments such that their alternating sums 
cancel each other out. We greedily build segments to try to make the overall 
sum of alternating sums equal to zero.

The approach:
1. First, check if the total sum of the array is even. If not, it's impossible to 
   partition into segments with alternating sums that sum to zero.
2. Then, we try to greedily form segments by extending current segment until 
   we can make the alternating sum of the current segment cancel out with 
   the remaining portion of the array.
3. We adjust the segments to ensure that their alternating sums sum to zero.

The algorithm tracks which positions have been used via boolean array `b` and 
uses a greedy approach to extend segments.
*/

#include <cstdio>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 2;
int T, n, s, k, a[N], l[N], r[N];
bool b[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), s = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i), s += a[i], b[i] = 0;
    if (s & 1) {
      printf("-1\n");
      continue;
    }
    s >>= 1, l[1] = r[1] = k = 1;
    for (int i = 2; i <= n; ++i)
      if (a[i] * s > 0 && !b[i - 1])
        s -= a[i], b[i] = 1, r[k] = i;
      else
        ++k, l[k] = r[k] = i;
    printf("%d\n", k);
    for (int i = 1; i <= k; ++i)
      printf("%d %d\n", l[i], r[i]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/