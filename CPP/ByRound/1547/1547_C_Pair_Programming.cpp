// Problem: CF 1547 C - Pair Programming
// https://codeforces.com/contest/1547/problem/C

#include <cstdio>
#include <vector>
// Purpose: This program reconstructs a valid sequence of actions from two sub-sequences,
// where each action is either adding a line (0) or modifying an existing line (positive number).
// It ensures that no modification is made to a line that doesn't exist yet.
// Algorithm: Two-pointer technique is used to merge the two sequences while maintaining
// the order of actions and ensuring valid line references.
// Time Complexity: O(n + m) per test case, where n and m are lengths of the action sequences
// Space Complexity: O(n + m) for storing the merged result sequence

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k, n, m;
    scanf("%ld %ld %ld", &k, &n, &m);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &b[p]);
    }
    long len(k), ta(0), tb(0);
    bool possible(true);
    std::vector<long> res(m + n, 0);
    for (long p = 0; p < m + n; p++) {
      // If Monocarp's actions are exhausted, take from Polycarp
      if (ta >= n) {
        res[p] = b[tb++];
      } else if (tb >= m) {
        // If Polycarp's actions are exhausted, take from Monocarp
        res[p] = a[ta++];
      } else if (a[ta] == 0) {
        // If Monocarp adds a line, prefer his action to maintain order
        res[p] = a[ta++];
      } else if (b[tb] == 0) {
        // If Polycarp adds a line, prefer his action to maintain order
        res[p] = b[tb++];
      } else if (a[ta] < b[tb]) {
        // If both modify existing lines, choose the one with smaller line number
        res[p] = a[ta++];
      } else if (b[tb] <= a[ta]) {
        // If both modify existing lines, choose the one with smaller line number
        res[p] = b[tb++];
      }
      // Update the length of the file
      len += (res[p] == 0);
      // Check if the action references an existing line
      if (res[p] > len) {
        possible = false;
        break;
      }
    }
    if (!possible) {
      puts("-1");
    } else {
      for (long p = 0; p < res.size(); p++) {
        printf("%ld ", res[p]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/