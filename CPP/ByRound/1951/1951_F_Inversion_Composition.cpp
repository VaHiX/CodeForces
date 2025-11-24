// Problem: CF 1951 F - Inversion Composition
// https://codeforces.com/contest/1951/problem/F

/*
 * Problem: F. Inversion Composition
 * 
 * Purpose:
 *   Given a permutation p and a target number of inversions k,
 *   find a permutation q such that inv(q) + inv(q * p) = k,
 *   or determine that it is impossible.
 * 
 * Algorithms/Techniques:
 *   - Binary Indexed Tree (Fenwick Tree) for efficient prefix sum queries and updates
 *   - Greedy approach with careful handling of inversion counts
 *   - Preprocessing to compute the base difference between inv(q) and inv(q * p)
 * 
 * Time Complexity:
 *   O(n log n) per test case due to BIT operations and iteration through elements
 * 
 * Space Complexity:
 *   O(n) for storing the permutation, BIT, and auxiliary arrays
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
#define ll long long
const int SZ = 1 << 20;
char buf[SZ], *p1, *p2;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SZ, stdin), p1 == p2) ? EOF    \
                                                                      : *p1++)
ll read() {
  ll n = 0;
  bool m = 0;
  char c = gc();
  while (c < '0' || c > '9')
    m = c == '-', c = gc();
  while (c >= '0' && c <= '9')
    n = (n << 3) + (n << 1) + (c ^ '0'), c = gc();
  return m ? -n : n;
}
const int N = 3e5 + 5;
int n, p[N], a[N], q[N], num, ans[N];
ll k;
void upd(int x, int y) {
  while (x <= n)
    a[x] += y, x += x & -x;
}
int ask(int x) {
  int y = 0;
  while (x)
    y += a[x], x -= x & -x;
  return y;
}
int main() {
  int T = read();
  while (T--) {
    n = read(), k = read();
    for (int i = 1; i <= n; i++)
      p[i] = read();
    for (int i = 1; i <= n; i++)
      a[i] = 0;
    // Calculate base adjustment using inversion count of p
    for (int i = 1; i <= n; i++)
      upd(p[i], 1), k -= i - ask(p[i]);
    // If k is negative or odd, impossible to achieve
    if (k < 0 || k & 1) {
      puts("NO");
      continue;
    }
    // If k is zero, identity permutation works
    if (k) {
      for (int i = 1; i <= n; i++)
        a[i] = 0;
      k >>= 1, num = 0;
      // Greedy placement of inversions to satisfy the remaining k
      for (int i = 1; i <= n; i++) {
        int x = ask(p[i]);
        if (x >= k) {
          // Found a valid position to place one inversion pair
          for (int j = 1; j < i; j++) {
            if (p[j] < p[i]) {
              if (!--k) {
                // Place numbers accordingly
                for (int y = i - 1; y > j; y--)
                  q[y] = ++num;
                q[i] = ++num;
                for (int y = j; y; y--)
                  q[y] = ++num;
                for (int y = i + 1; y <= n; y++)
                  q[y] = ++num;
                break;
              }
            }
          }
          break;
        }
        k -= x, upd(p[i], 1);
      }
      if (k) {
        puts("NO");
        continue;
      }
    } else {
      // k = 0, use identity permutation
      for (int i = 1; i <= n; i++)
        q[i] = i;
    }
    // Compute the final result using q * p
    for (int i = 1; i <= n; i++)
      ans[p[i]] = q[i];
    puts("YES");
    for (int i = 1; i <= n; i++)
      printf("%d ", ans[i]);
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/