// Problem: CF 1330 B - Dreamoon Likes Permutations
// https://codeforces.com/contest/1330/problem/B

/*
Algorithm: 
- The problem requires finding all valid ways to split the array `a` into two permutations `p1` and `p2`.
- A permutation of length `l` contains all integers from 1 to `l` exactly once.
- For a valid split at position `i`, the prefix `a[0:i]` must form a permutation of length `i`, and the suffix `a[i:n]` must form a permutation of length `n - i`.

Approach:
- Preprocess all valid prefix lengths using a set to track unique elements and check if the prefix forms a valid permutation.
- Similarly, process all valid suffix lengths from the end.
- Match valid prefixes and suffixes to find all valid splits.

Time Complexity: O(n * log n) per test case due to set operations.
Space Complexity: O(n) for storing sets and results.
*/

#include <cstdio>
#include <set>
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
    std::set<long> s;           // Set to store unique elements in prefix
    std::set<long> left;        // Set to store valid prefix end indices
    long mx(0);                 // Maximum element encountered so far
    for (long p = 0; p < n; p++) {
      if (s.count(a[p])) {      // If duplicate element found, break
        break;
      }
      s.insert(a[p]);           // Add element to set
      mx = (mx > a[p]) ? mx : a[p];  // Update maximum
      if (s.size() == mx) {     // If size equals max, valid permutation
        left.insert(p);         // Mark this as valid prefix end
      }
    }
    std::set<long> t;           // Set to store unique elements in suffix
    mx = 0;                     // Reset max
    std::vector<long> ans;      // Vector to store valid split points
    for (long p = n - 1; p >= 0; p--) {
      if (t.count(a[p])) {      // If duplicate in suffix, break
        break;
      }
      t.insert(a[p]);           // Add element to suffix set
      mx = (mx > a[p]) ? mx : a[p];  // Update max
      if (t.size() == mx && left.count(p - 1)) {  // Valid suffix with matching prefix
        ans.push_back(p);       // Record valid split point
      }
    }
    printf("%ld\n", ans.size());  // Print number of valid splits
    for (long p = 0; p < ans.size(); p++) {
      printf("%ld %ld\n", ans[p], n - ans[p]);  // Print split lengths
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/