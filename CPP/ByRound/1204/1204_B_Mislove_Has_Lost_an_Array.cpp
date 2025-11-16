// Problem: CF 1204 B - Mislove Has Lost an Array
// https://codeforces.com/contest/1204/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  ll n, l, r;
  scanf("%lld %lld %lld", &n, &l, &r);
  // Calculate minimum possible sum
  ll fl = (n - l + 1); // Start with l-1 ones and one element to make up the rest
  for (long p = 1; p < l; p++) {
    fl += (1 << p); // Add powers of 2 to represent the minimal structure
  }
  --r;
  // Calculate maximum possible sum
  ll fr = 0;
  for (long p = 0; p < n; p++) {
    fr += (1 << ((p < r) ? p : r)); // Build a tree-like structure with max elements
  }
  printf("%lld %lld\n", fl, fr);
  return 0;
}
/*
Problem: Mislove Has Lost an Array
Purpose: Given array properties, compute minimum and maximum possible sums of all elements.
Algorithms/Techniques: Greedy approach, bit manipulation
Time Complexity: O(l + n)
Space Complexity: O(1)
*/

// https://github.com/VaHiX/codeForces/