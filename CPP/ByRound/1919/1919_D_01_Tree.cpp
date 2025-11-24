// Problem: CF 1919 D - 01 Tree
// https://codeforces.com/contest/1919/problem/D

/*
Purpose: Determine if a given array of distances from root to leaves in DFS order can be represented by a valid complete binary tree where each internal edge has weight 0 or 1.

Algorithm:
- The key insight is that in a valid tree, each leaf's distance from the root must obey certain constraints based on the tree structure.
- For a complete binary tree with n leaves, we simulate the process of building the tree and check the consistency of the input array.
- We use a monotonic stack approach to precompute for each element the largest previous value smaller than current element (pre array) and the smallest next value larger than current element (suf array).
- Then, for each leaf, we check that either the previous or the next element is one less than its distance, which ensures the path to the leaf is valid.

Time Complexity: O(n) per test case
Space Complexity: O(n) for arrays and stack usage

Techniques:
- Monotonic stack
- Preprocessing with stack to find nearest smaller elements
- Constraint validation based on tree structure properties
*/

#include <cstdio>
#include <utility>

#define N 200005
#define P 1000000007
#define INF 1061109567
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef unsigned long long ull;
char buf[1 << 20], *p1, *p2;
#define GC                                                                     \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? 0                                                                     \
       : *p1++)
inline ll read() {
  ll x = 0, f = 1;
  char ch = GC;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = GC;
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = GC;
  }
  return x * f;
}
int n, cnt0, a[N], pre[N], suf[N];
int R, q[N];
void Solve() {
  n = read();
  cnt0 = 0;
  for (int i = 1; i <= n; i++)
    a[i] = read(), cnt0 += !a[i];  // Count number of 0s
  if (cnt0 != 1) {  // Root must have exactly one path of weight 0
    printf("NO\n");
    return;
  }
  a[0] = a[n + 1] = -1;
  q[R = 1] = 0;
  for (int i = 1; i <= n; i++) {
    while (R && a[q[R]] >= a[i])  // Maintain decreasing order in stack
      R--;
    pre[i] = a[q[R]];  // Store previous smaller element
    q[++R] = i;
  }
  q[R = 1] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (R && a[q[R]] >= a[i])
      R--;
    suf[i] = a[q[R]];  // Store next smaller element
    q[++R] = i;
  }
  for (int i = 1; i <= n; i++)
    if (pre[i] != a[i] - 1 && suf[i] != a[i] - 1) {  // Check constraints
      printf("NO\n");
      return;
    }
  printf("YES\n");
}
int main() {
  for (int T = read(); T--;)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/