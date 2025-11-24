// Problem: CF 1685 C - Bring Balance
// https://codeforces.com/contest/1685/problem/C

/*
Algorithm: Greedy + Bracket Balance Analysis
Time Complexity: O(n) for each test case, where n is the length of the string
Space Complexity: O(n) for storing the prefix sum array

The algorithm works by:
1. Computing a prefix sum array where '(' contributes +1 and ')' contributes -1
2. Identifying the point where the prefix sum reaches its minimum
3. Using greedy reversal operations to fix the imbalance:
   - If the entire sequence is not balanced, we may need 1 or 2 operations
   - The check function attempts to find a single operation that fixes everything
   - If not possible, we use exactly 2 operations: one to balance the prefix and another to fix the suffix
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 200005;
int T, n, a[N];
char s[N];
bool check() {
  int l = 1;
  // Find leftmost position where prefix sum is minimal
  for (int i = 1; i <= n && a[i] >= 0; i++)
    if (a[l - 1] <= a[i])
      l = i + 1;
  int r = n;
  // Find rightmost position where prefix sum is minimal
  for (int i = n; i >= 1 && a[i] >= 0; i--)
    if (a[r] <= a[i])
      r = i;
  // Check if this range can be fixed with one operation
  for (int i = l; i <= r; i++)
    if (a[l - 1] + a[r] < a[i])
      return false;
  printf("1\n%d %d\n", l, r);
  return true;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    n *= 2;
    bool flag = true;
    int pos = 0;
    // Calculate prefix sums and determine if balanced at each step
    for (int i = 1; i <= n; i++) {
      a[i] = a[i - 1] + (s[i] == '(' ? 1 : -1), flag &= (a[i] >= 0);
      if (a[pos] <= a[i])
        pos = i;
    }
    if (flag) {
      puts("0");
      continue;
    }
    // Try single operation
    if (check())
      continue;
    // If single operation not sufficient, use two operations
    printf("2\n%d %d\n%d %d\n", 1, pos, pos + 1, n);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/