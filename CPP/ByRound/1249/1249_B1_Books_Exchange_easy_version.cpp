// Problem: CF 1249 B1 - Books Exchange (easy version)
// https://codeforces.com/contest/1249/problem/B1

/*
 * Problem: Books Exchange (easy version)
 * Algorithm: Cycle Detection in Permutations
 * Time Complexity: O(n) per query
 * Space Complexity: O(n) per query
 *
 * Description:
 * Each kid has a book, and every day the books are passed according to a permutation p.
 * We need to find for each kid the number of days after which their book returns to them.
 * This is equivalent to finding the cycle length in the permutation graph starting from each node.
 */

#include <cstdio>
#include <vector>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1, 0);  // stores the permutation p
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<bool> b(n + 1, 0);     // marks visited nodes
    std::vector<long> dur(n + 1, 0);   // stores cycle lengths for each node
    for (long p = 1; p <= n; p++) {
      if (b[p]) {                      // skip if already processed
        continue;
      }
      std::vector<long> cycle;         // collect nodes in current cycle
      long cur(p);
      while (!b[cur]) {
        b[cur] = 1;                    // mark as visited
        cycle.push_back(cur);          // add to cycle
        cur = a[cur];                  // move to next node in permutation
      }
      for (long k = 0; k < cycle.size(); k++) {
        dur[cycle[k]] = cycle.size();  // assign cycle length to all nodes in cycle
      }
    }
    for (long p = 1; p <= n; p++) {
      printf("%ld ", dur[p]);          // output result for each kid
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/