// Problem: CF 1691 B - Shoe Shuffling
// https://codeforces.com/contest/1691/problem/B

/*
B. Shoe Shuffling
Algorithm: Greedy + Grouping
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem requires us to redistribute shoes among students such that:
1. No student gets their own shoes (p[i] != i)
2. Each student gets shoes of size >= their own size

Approach:
- Group consecutive equal elements together.
- For each group, we determine how to assign shoes properly.
- If any group has only one element, then we can't redistribute without assigning
  that student their own shoe — hence impossible.
- In the case where all items are equal, any valid permutation is acceptable.

Key logic:
We iterate through the array and group consecutive elements with same value.
For groups of size > 1, we attempt to assign shoes in a cyclic manner.
If any group has size 1, output -1.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    // Add sentinel to simplify loop termination
    v.push_back(1e9 + 7);
    long sz(1), start(0);
    bool possible(true);
    std::vector<long> w;
    for (long p = 1; p <= n; p++) {
      // If current element equals previous one, increment group size
      if (v[p] == v[p - 1]) {
        ++sz;
        continue;
      }
      // If group size is 1, impossible to reassign without giving self
      if (sz == 1) {
        possible = false;
        break;
      }
      // Record the start of new group and assign indices properly
      w.push_back(p);
      for (long u = start; u < p - 1; u++) {
        w.push_back(u + 1);
      }
      start = p;
      sz = 1;
    }
    if (possible) {
      for (long p = 0; p < w.size(); p++) {
        printf("%ld ", w[p]);
      };
      puts("");
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/