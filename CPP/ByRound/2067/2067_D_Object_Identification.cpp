// Problem: CF 2067 D - Object Identification
// https://codeforces.com/contest/2067/problem/D

/*
 * Problem: D. Object Identification
 * Purpose: Determine whether the hidden object is a directed graph (Object A) or a set of points on a coordinate plane (Object B)
 * Algorithms/Techniques:
 *   - Interactive problem using queries to distinguish between two objects
 *   - Uses properties of graph distances vs Manhattan distances
 *   - Time Complexity: O(n) per test case
 *   - Space Complexity: O(n)
 *
 * Object A: Directed graph with edges x[i] -> y[i]
 * Object B: Points (x[i], y[i]) on a 2D plane
 *
 * Strategy:
 *   - If there are duplicates in array x, then it's impossible to form a valid permutation for Graph A => Object B
 *   - Otherwise, query two specific pairs and compare results:
 *     - For Graph A: shortest paths will be at least n-1 if nodes are disconnected or not in a line
 *     - For Manhattan distance: values depend on coordinates
 */
#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 3;
int T, n, x[N], knd, inp, inp2, a, b, cnt[N];
inline void qry(int x, int y) { printf("? %d %d\n", x, y), fflush(stdout); }
int main() {
  scanf("%d", &T);
  while (T--) {
    knd = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      cnt[i] = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &x[i]);
    // Check if there are duplicate values in x (indicating invalid graph structure)
    for (int i = 1; i <= n; i++) {
      if (cnt[x[i]])
        knd = 1;
      cnt[x[i]] = 1;
    }
    if (knd) {
      // If duplicates exist, it's likely Object B
      for (int i = 1; i <= n; i++)
        if (!cnt[i])
          knd = i; // Find missing number from 1 to n
      qry(knd, 1 + (knd == 1)); // Query with a safe pair that avoids index 0
      scanf("%d", &inp);
      if (inp)
        printf("! B\n");
      else
        printf("! A\n");
    } else {
      // No duplicates: check for special conditions where it's definitely Object A or B
      for (int i = 1; i <= n; i++) {
        if (x[i] == 1)
          a = i;
        if (x[i] == n)
          b = i;
      }
      qry(a, b), scanf("%d", &inp);
      qry(b, a), scanf("%d", &inp2);
      // Compare queries result
      if (inp >= n - 1 && inp == inp2)
        printf("! B\n");
      else
        printf("! A\n");
    }
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/