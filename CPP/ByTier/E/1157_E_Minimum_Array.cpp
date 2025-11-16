// Problem: CF 1157 E - Minimum Array
// https://codeforces.com/contest/1157/problem/E

/*
E. Minimum Array
Algorithm: Greedy with multiset
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem asks to reorder array b to minimize the lexicographically smallest array c,
where c[i] = (a[i] + b[i]) % n.

Approach:
- For each element a[i] in array a, we want to find the smallest possible value of (a[i] + b[i]) % n.
- To do this greedily, we use a multiset to keep elements of b in sorted order.
- For each a[i], compute target = (2*n - a[i]) % n. This is the value that minimizes c[i] when added to a[i].
- Find the smallest element in multiset >= target using lower_bound.
- If no such element exists, take the smallest (wrap around).
- Add this chosen b[i] to result and remove it from multiset.

This ensures we make the lexicographically smallest array c possible by always choosing
the best available b[i] for each a[i].
*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::multiset<long> s;
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    s.insert(x);
  }
  for (long p = 0; p < n; p++) {
    const long x = (2 * n - a[p]) % n; // Compute target value to minimize sum
    std::multiset<long>::iterator it = s.lower_bound(x); // Find first element >= x
    if (it == s.end()) {
      it = s.begin(); // Wrap around to smallest element
    }
    printf("%ld ", (a[p] + *it) % n); // Add a[i] and chosen b[i], modulo n
    s.erase(it); // Remove chosen element from multiset
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/