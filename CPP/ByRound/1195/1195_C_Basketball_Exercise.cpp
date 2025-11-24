// Problem: CF 1195 C - Basketball Exercise
// https://codeforces.com/contest/1195/problem/C

/*
C. Basketball Exercise
Algorithm: Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(n)

The problem is about selecting a team of students from two rows such that:
- No two consecutive selected students are from the same row.
- The index of each chosen student (after the first) must be strictly greater than the previous one.
- Goal is to maximize the total height of chosen students.

This is solved using dynamic programming where for each position we track:
- fa[p]: maximum height sum ending at position p in row 1
- fb[p]: maximum height sum ending at position p in row 2
- fc[p]: maximum height sum ending at any position up to p (used for transitions)

Transition:
fa[p] = a[p] + max(fb[p-1], fc[p-1]) // Choose from row 1, previous was row 2 or any
fb[p] = b[p] + max(fa[p-1], fc[p-1]) // Choose from row 2, previous was row 1 or any
fc[p] = max(fa[p-1], fb[p-1])        // Don't choose current, take best so far

Finally, answer is max(fa[n-1], fb[n-1])
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  std::vector<ll> b(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &b[p]);
  }
  std::vector<ll> fa(n, 0), fb(n, 0), fc(n, 0);
  fa[0] = a[0];             // Initialize first element of row 1
  fb[0] = b[0];             // Initialize first element of row 2
  fc[0] = 0;                // No elements chosen yet
  for (ll p = 1; p < n; p++) {
    fa[p] = a[p] + (fb[p - 1] > fc[p - 1] ? fb[p - 1] : fc[p - 1]); // Max sum ending at row 1
    fb[p] = b[p] + (fa[p - 1] > fc[p - 1] ? fa[p - 1] : fc[p - 1]); // Max sum ending at row 2
    fc[p] = (fa[p - 1] > fb[p - 1] ? fa[p - 1] : fb[p - 1]);        // Best so far from any row
  }
  ll ans = (fa.back() > fb.back()) ? fa.back() : fb.back();   // Final answer is max of last elements
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/