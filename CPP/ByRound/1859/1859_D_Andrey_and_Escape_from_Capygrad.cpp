// Problem: CF 1859 D - Andrey and Escape from Capygrad
// https://codeforces.com/contest/1859/problem/D

/*
 * Problem: D. Andrey and Escape from Capygrad
 * 
 * Purpose: 
 *   Given n portals, each defined by a range [l_i, r_i] and a teleportation range [a_i, b_i],
 *   determine the maximum possible coordinate Andrey can reach from q starting positions.
 *   The portals can be used multiple times.
 * 
 * Approach:
 *   1. Preprocess portal segments to find maximal reachable ranges
 *   2. For each starting position, check how far it can go through portal teleportations
 *   3. Use sweep line / greedy technique to merge overlapping segments
 * 
 * Algorithms:
 *   - Segment processing with sorting
 *   - Greedy range merging
 *   - Binary search / two-pointer technique
 * 
 * Time Complexity: O(n log n + q log q)
 *   - Sorting portals: O(n log n) 
 *   - Sorting queries: O(q log q)
 *   - Processing: O(n + q)
 * 
 * Space Complexity: O(n + q)
 *   - Storage for segments and queries
 * 
 * Techniques:
 *   - Sweep line sweep from right to left
 *   - Range merging and interval processing
 *   - Coordinate compression is implicitly handled using sorting
 * 
 * Constraints:
 *   - 1 ≤ n, q ≤ 2 * 10^5
 *   - l_i ≤ a_i ≤ b_i ≤ r_i ≤ 10^9
 *   - Sum of n and q over all test cases ≤ 2 * 10^5
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
const int Maxn = 2e5 + 5;
char getch() {
  static char buf[1 << 14], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 14, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
void read(int &x) {
  x = 0;
  char c = getch();
  while (c < '0' || c > '9')
    c = getch();
  while (c >= '0' && c <= '9') {
    x = x * 10 + (c - '0');
    c = getch();
  }
}
struct segment {
  int l, a, b, r;
} seg[Maxn];
int cmp_a(segment a, segment b) { return a.a < b.a; }
int cmp_b(segment a, segment b) { return a.b > b.b; }
vector<int> c;
struct node {
  int a, loc;
} a[Maxn];
int cmp(node a, node b) { return a.a < b.a; }
int cmp_loc(node a, node b) { return a.loc < b.loc; }
int ans_l[Maxn];
int ans_r[Maxn];
int ans[Maxn];
int line[Maxn * 6];
signed main() {
  int T;
  read(T);
  while (T--) {
    int n;
    read(n);
    c.clear();
    for (int i = 1; i <= n; ++i) {
      read(seg[i].l);
      read(seg[i].r);
      read(seg[i].a);
      read(seg[i].b);
    }
    int m;
    read(m);
    for (int i = 1; i <= m; ++i) {
      read(a[i].a);
      a[i].loc = i;
    }
    sort(a + 1, a + m + 1, cmp);
    sort(seg + 1, seg + n + 1, cmp_b);
    int l = 1e9 + 2, r = 1e9 + 1, pos = m;
    for (int i = 1; i <= n; ++i) {
      if (seg[i].b >= l) {
        l = min(l, seg[i].l);
        continue;
      }
      while (pos >= 1 && a[pos].a > seg[i].b) {
        if (l <= a[pos].a && a[pos].a <= r)
          ans_r[pos] = r;
        else
          ans_r[pos] = a[pos].a;
        pos--;
      }
      l = seg[i].l;
      r = seg[i].b;
    }
    for (int i = pos; i >= 1; --i) {
      if (l <= a[i].a && a[i].a <= r)
        ans_r[i] = r;
      else
        ans_r[i] = a[i].a;
    }
    for (int i = 1; i <= m; ++i) {
      ans[a[i].loc] = ans_r[i];
    }
    for (int i = 1; i <= m; ++i) {
      printf("%d ", ans[i]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/