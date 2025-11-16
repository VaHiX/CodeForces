// Problem: CF 1559 C - Mocha and Hiking
// https://codeforces.com/contest/1559/problem/C

/*
Code Purpose:
This program solves the problem of finding a Hamiltonian path through all villages in a directed graph, 
where the graph has a specific structure: n+1 villages and 2n-1 directed roads. The roads are of two types:
1. Linear roads from village i to village i+1.
2. Special roads from village i to village n+1 or vice versa, depending on the value of a[i].

The algorithm determines a valid traversal order by identifying a critical point where a transition
from a backward edge (from n+1 to i) to a forward edge (from i to n+1) causes a break in the linear order.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the input array a
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<int> a(n);
    long move(-1);
    for (long p = 0; p < n; p++) {
      scanf("%d", &a[p]);
      // Determine where to insert the special village (n+1) in the traversal
      if (p == 0 && a[0] == 1) {
        // If the first element is 1, start with village n+1
        move = -1;
      } else if (p == n - 1 && a.back() == 0) {
        // If last element is 0, end with village n+1
        move = n - 1;
      } else if (p > 0 && a[p - 1] == 0 && a[p] == 1) {
        // Transition from 0 to 1 means we must insert n+1 here to maintain valid path
        move = p - 1;
      }
    }
    if (move < 0) {
      // If we haven't found a specific insertion, start with village n+1
      printf("%ld ", n + 1);
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", p + 1);
      if (move == p) {
        // Insert village n+1 after the identified position
        printf("%ld ", n + 1);
      }
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/