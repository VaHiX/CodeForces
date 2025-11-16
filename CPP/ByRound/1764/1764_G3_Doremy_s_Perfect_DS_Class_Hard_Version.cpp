// Problem: CF 1764 G3 - Doremy's Perfect DS Class (Hard Version)
// https://codeforces.com/contest/1764/problem/G3

/*
 * Problem: Find the index of element 1 in a permutation of size n using at most 20 queries.
 * 
 * Algorithm/Techniques:
 * - Binary search approach on the permutation indices to locate where p[i] = 1.
 * - Uses floor division queries Q(l, r, k) to count distinct values in a subarray after division.
 * - Implements recursive search tree traversal with smart query selection to reduce search space.
 * 
 * Time Complexity: O(log^2 n) due to binary search and recursive subdivision.
 * Space Complexity: O(log n) for recursion stack due to depth of recursive calls.
 */

#include <stdlib.h>
#include <iostream>

#define I int
using namespace std;
I n, l = 1, r, pos, ok, M, x, y, L, R;
I Q(I l, I r, I x = 2) {
  cout << "? " << l << ' ' << r << ' ' << x << endl;
  cin >> x;
  return x;
}
void G(I l) { cout << "! " << l << endl, exit(0); }
void F(I l, I r, I A, I B, I C, I D) {
  if (l == r)
    G(l);
  if (l + 1 == r)
    (!ok) ? ((l == 1) ? G((Q(r, r + 1, n) == 2) ? l : r)
                      : G((Q(l - 1, l, n) == 2) ? r : l))
          : ((A - B == 1) ? G((Q(1, l) == B) ? r : l)
                          : G((Q(r, n) == D) ? l : r));
  M = (l + r) >> 1, x = Q(1, M), y = Q(M + 1, n),
  L = (x - B + C - y > M - l + 1), R = (A - x + y - D > r - M),
  (L & R) ? Q(l, M, n) > 1 ? (ok = 1, F(M + 1, r, A, x, y, D))
                           : (ok = 1, F(l, M, x, B, C, y))
  : L ? F(l, M, x, B, C, y)
          : F(M + 1, r, A, x, y, D);
}
int main() {
  cin >> n, ok = (n & 1), r = n, F(1, n, (n >> 1) + 1, 0, (n >> 1) + 1, 0);
}


// https://github.com/VaHiX/CodeForces/