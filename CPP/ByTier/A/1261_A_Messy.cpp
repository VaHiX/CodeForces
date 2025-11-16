// Problem: CF 1261 A - Messy
// https://codeforces.com/contest/1261/problem/A

#include <stdio.h>
#include <algorithm>
#include <utility>

#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define pii pair<int, int>
using namespace std;
const int N = 2009;
char s[N];
pii ans[N];

/*
 * Algorithm: 
 * 1. Find the first unmatched closing bracket from left and first unmatched opening bracket from right
 * 2. Reverse the substring between them to make them match
 * 3. Continue until all brackets are matched
 * 4. Then add k-1 additional operations to ensure exactly k prefixes are regular
 * 
 * Time Complexity: O(n^2) - due to reversing operations and potential multiple iterations
 * Space Complexity: O(n) - for the string and answer array
 */
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    int l = 1, r = n, cnt = 0;
    
    // Find mismatched brackets and fix them by reversing substrings
    while (l <= r) {
      while (s[l] == '(')
        ++l;
      while (s[r] == ')')
        --r;
      if (l > r)
        break;
      reverse(s + l, s + r + 1);
      ans[cnt++] = {l, r};
    }
    
    // Output all reversal operations + additional k-1 operations to create exactly k regular prefixes
    printf("%d\n", cnt + k - 1);
    rep(i, 0, cnt) { printf("%d %d\n", ans[i].first, ans[i].second); }
    rep(i, 1, k) printf("%d %d\n", 2 * i, n / 2 + i);
  }
}


// https://github.com/VaHiX/CodeForces/