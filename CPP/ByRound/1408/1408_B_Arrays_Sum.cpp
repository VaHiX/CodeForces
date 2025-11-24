// Problem: CF 1408 B - Arrays Sum
// https://codeforces.com/contest/1408/problem/B

/*
B. Arrays Sum
Algorithm: Greedy + Set-based analysis
Time Complexity: O(n log n) per test case due to set operations
Space Complexity: O(n) for storing elements in the set

Given a non-decreasing array of non-negative integers and a positive integer k,
we want to decompose the array into m arrays such that:
1. Each b_i has size n
2. a_j = sum(b_{i,j}) for all j
3. Each b_i has at most k distinct values

The approach:
- If k == 1, then each element in b_i must be same; so if there are multiple distinct values in a, impossible (-1)
- Otherwise, use greedy to determine minimum number of arrays needed by counting how many "groups" we need
  based on the number of unique elements and k.
*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::set<long> s;
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      s.insert(a); // Insert all elements into set to get unique values
    }
    if (k == 1) {
      // If k=1, each array b_i can only have one distinct value.
      // So we can only represent a if all elements in a are same.
      // If there's more than one distinct element, it's impossible.
      printf("%ld\n", 1L - 2 * (s.size() > 1)); // Returns -1 if s.size() > 1, otherwise 1
    } else {
      // Greedy approach: use formula to compute minimum m.
      // (s.size() - 1 + k - 2) / (k - 1) simulates how many segments needed.
      long ans = (s.size() - 1 + k - 2) / (k - 1);
      ans = (ans > 0) ? ans : 1; // Ensure at least 1 array
      printf("%ld\n", ans);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/