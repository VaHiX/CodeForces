// Problem: CF 739 A - Alyona and mex
// https://codeforces.com/contest/739/problem/A

/*
Purpose: This code solves the problem of constructing an array of n non-negative integers such that the minimum mex (minimum excludant) among m given subarrays is maximized.

Approach:
- For each subarray, we calculate its length.
- We find the minimum length across all subarrays. Let this be `len`.
- The idea is that if we can ensure that every subarray has at least `len` distinct elements, then the mex of each subarray will be at least `len`.
- We construct the array by repeating the sequence 0, 1, ..., (len - 1) cyclically to fill the array of size n.

Time Complexity: O(m + n), where m is the number of subarrays and n is the size of the array.
Space Complexity: O(1), as we only use a constant amount of extra space apart from input storage.

Algorithms/Techniques:
- Greedy approach with cyclic repetition
- Prefix analysis for minimum subarray length
*/

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m;
  std::cin >> n >> m;
  long len(n + 1);  // Initialize len to a large value to find minimum later
  while (m--) {
    long a, b;
    std::cin >> a >> b;
    long temp = b - a + 1;  // Calculate length of current subarray
    len = (len < temp) ? len : temp;  // Keep track of minimum length
  }
  std::cout << len << std::endl;
  for (int p = 0; p < n; p++) {
    std::cout << (p % len) << " ";  // Fill the array cyclically with 0 to len-1
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/