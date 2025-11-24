// Problem: CF 1931 C - Make Equal Again
// https://codeforces.com/contest/1931/problem/C

/*
C. Make Equal Again
Algorithm: Two-pointer technique with prefix/suffix matching.
Time Complexity: O(n) amortized over all test cases.
Space Complexity: O(n) for the vector storage.

Approach:
- We aim to make all elements equal using one operation that changes a subarray.
- The key insight is to find the maximum number of elements we can leave unchanged by matching
  prefixes and suffixes with the first and last elements of the array, respectively.
- If the first and last elements are the same, we can potentially combine prefix and suffix matches.
- We compute how many elements we can keep as they are, then subtract from total length to get cost.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long left(1);  // Count how many elements from the start match a[0]
    while (left < n && a[left] == a[0]) {
      ++left;
    }
    long right(1);  // Count how many elements from the end match a[n-1]
    while (right + 1 <= n && a[n - 1 - right] == a.back()) {
      ++right;
    }
    long s(left > right ? left : right);  // Take max of prefix/suffix matches
    if (a[0] == a.back()) {               // If first and last elements are same,
      s = left + right;                   // we can merge prefix and suffix
    }
    s = (s < n ? s : n);  // Ensure s does not exceed array size
    printf("%ld\n", n - s);  // Minimum cost = total length minus matched elements
  }
}


// https://github.com/VaHiX/codeForces/