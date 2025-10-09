// Problem: CF 2146 C - Wrong Binary Search
// https://codeforces.com/contest/2146/problem/C

/*
C. Wrong Binary Search
Algorithms/Techniques: 
  - Greedy construction with segment reversal
  - Segment processing based on consecutive same characters in binary string
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

The problem asks to construct a permutation such that an element i is "stable" 
if and only if s[i] == '1'. An element x is stable if the binary search-like 
function find(x) always returns a valid index where p[find(x)] == x, regardless
of how mid-point is chosen during the search.

Key insight:
  - If s[i] == '1', then i must be stable. This means that after all operations,
    the value at position i in the permutation should not conflict with 
    what's expected from binary search.
  - If s[i] == '0', then i must NOT be stable.

The algorithm processes the string by grouping consecutive identical characters,
and for groups of '0's, we reverse the corresponding segment of the permutation.
For a group of '0's, if there is only a single element (i==j) and we reverse it,
that element will incorrectly become stable. Thus, we check for this case.

The approach:
1. Process each group of consecutive same characters in s.
2. For group of '1's: do nothing — keep the current permutation order.
3. For group of '0's: reverse the corresponding segment in p to make elements unstable.
4. Special care is taken when a '0' is standalone (i == j), which causes a conflict.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 200010;
int n;
char s[N];
int p[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++)
      p[i] = i; // Initialize permutation as [1,2,...,n]
    bool success = true;
    for (int i = 1; i <= n; i++) {
      int j = i;
      // Find the end of the current group of same characters
      while (j < n && s[j + 1] == s[i])
        j++;
      if (s[i] == '0') {
        // If this is a single '0', it's not allowed to reverse since it would make that element stable.
        if (i == j)
          success = false;
        reverse(p + i, p + j + 1); // Reverse the segment corresponding to the group of '0's
      }
      i = j; // Skip to end of current group
    }
    if (!success)
      puts("NO");
    else {
      puts("YES");
      for (int i = 1; i <= n; i++)
        printf("%d ", p[i]);
      puts("");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/