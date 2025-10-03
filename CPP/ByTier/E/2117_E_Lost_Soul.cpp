// Problem: CF 2117 E - Lost Soul
// https://codeforces.com/contest/2117/problem/E

/*
E. Lost Soul
Algorithms/Techniques: Greedy, Simulation, Array Manipulation

Time Complexity: O(n) amortized per test case, where n is the length of arrays a and b.
Space Complexity: O(n), for storing the input arrays and the seen array.

The problem involves maximizing the number of matching positions between two arrays
by performing allowed operations. The key insight is to avoid unnecessary operations
by identifying critical points in the arrays where a match can be formed or maintained,
and to consider removing one element optimally.

The solution works as follows:
1. If the last elements of both arrays already match, we return n (all positions match).
2. Otherwise, we traverse from the second-to-last element backward.
3. For each position, we check whether:
   - The current elements match.
   - The current element matches with its successor in either array.
   - The current elements have been seen before (to avoid unnecessary operations).
4. If any of these conditions hold, we record this as a critical point.
5. We then determine how many matches can be achieved by considering if we remove
   an element, and adjust accordingly.

The algorithm avoids overcomplicating the process by only tracking key transitions,
not simulating every single operation, leading to efficient performance.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    for (long &x : a) {
      scanf("%ld", &x);
    }
    for (long &x : b) {
      scanf("%ld", &x);
    }
    std::vector<bool> seen(n + 1, 0);  // Track which values have been processed
    if (a.back() == b.back()) {        // If last elements already match
      printf("%ld\n", n);
      continue;
    }
    long cnt(-1);
    for (long p = n - 2; cnt < 0 && p >= 0; p--) {
      // Check if we can avoid operations at this position or if it's safe to process
      if (a[p] == b[p] || a[p] == a[p + 1] || b[p] == b[p + 1] || seen[a[p]] ||
          seen[b[p]]) {
        cnt = p;
      }
      seen[a[p + 1]] = seen[b[p + 1]] = true;  // Mark next elements as processed
    }
    printf("%ld\n", cnt + 1);  // Return how many elements to keep (0-indexed)
  }
}


// https://github.com/VaHiX/codeForces/