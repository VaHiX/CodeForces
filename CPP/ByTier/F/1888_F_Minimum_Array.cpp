// Problem: CF 1888 F - Minimum Array
// https://codeforces.com/contest/1888/problem/F

/*
 * Problem: F. Minimum Array
 * Algorithm: Difference Array + Lazy Propagation Simulation
 * Time Complexity: O(n + q)
 * Space Complexity: O(n)
 *
 * Approach:
 * 1. Use a difference array technique to simulate range updates efficiently.
 * 2. Keep track of non-zero elements in a set to quickly determine the first
 *    negative value which would lead to a lexicographically smaller array.
 * 3. Once a negative value is encountered, we stop applying further operations
 *    and compute the final result by accumulating the tags.
 * 4. The tag array stores the cumulative effect of all operations up to a point.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <array>
#include <set>
#include <vector>

#define ll long long
using namespace std;
const int N = 5e5 + 5;
char getch() {
  static char buf[100000], *s1, *s2;
  return (s1 == s2) && (s2 = (s1 = buf) + fread(buf, 1, 100000, stdin)),
         s1 == s2 ? EOF : *s1++;
}
int read() {
  int x = 0, w = 1;
  char ch = 1;
  while (!isdigit(ch)) {
    if (ch == '-')
      w = -1;
    ch = getch();
  }
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x * w;
}
int t, n, q;
int a[N];
ll b[N], tag[N]; // b: difference array, tag: lazy propagation array
void init() {
  for (int i = 0; i <= n + 1; ++i)
    b[i] = tag[i] = 0;
}
void charming() {
  init();
  n = read();
  for (int i = 1; i <= n; ++i)
    a[i] = read();
  q = read();
  set<int> nonZero;  // Keep track of indices where b[i] != 0
  vector<array<int, 3>> cge;  // Stores operations (l, r, x)
  int best = 0;  // Index of the last operation to be applied
  for (int i = 1, l, r, x; i <= q; ++i) {
    l = read(), r = read(), x = read();
    cge.emplace_back((array<int, 3>){l, r, x});
    b[l] += x;  // Apply difference array update
    if (b[l] == 0 && nonZero.count(l))
      nonZero.erase(l); // Update set if b[l] becomes 0
    if (b[l] != 0 && !nonZero.count(l))
      nonZero.insert(l); // Update set if b[l] becomes non-zero
    b[r + 1] -= x;
    if (b[r + 1] == 0 && nonZero.count(r + 1))
      nonZero.erase(r + 1);
    if (b[r + 1] != 0 && !nonZero.count(r + 1))
      nonZero.insert(r + 1);
    if (nonZero.size()) {
      int fir = *nonZero.begin();
      if (b[fir] < 0) {  // Found first negative value
        best = i;  // Stop applying further operations
        for (int idx : nonZero)
          b[idx] = 0;  // Reset the difference array
        nonZero.clear();
      }
    }
  }
  // Apply operations up to 'best' index to the tag array
  for (int i = 0, l, r, x; i < best; ++i) {
    l = cge[i][0], r = cge[i][1], x = cge[i][2];
    tag[l] += x, tag[r + 1] -= x;
  }
  ll sum = 0;
  // Output the final result by accumulating the tags and adding original array
  for (int i = 1; i <= n; ++i) {
    sum = sum + tag[i];
    printf("%lld%c", sum + a[i], i == n ? '\n' : ' ');
  }
}
signed main() {
  t = read();
  while (t--)
    charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/