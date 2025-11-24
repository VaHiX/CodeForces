// Problem: CF 1690 D - Black and White Stripe
// https://codeforces.com/contest/1690/problem/D

/*
D. Black and White Stripe

Purpose:
This program finds the minimum number of white cells that need to be recolored to black 
in order to obtain a contiguous segment of exactly k consecutive black cells in a given string.
The solution uses a sliding window technique over a prefix sum array.

Algorithm:
- Use a prefix sum array to efficiently count black cells up to each index.
- Slide a window of size k across the string and compute how many white cells 
  are inside each window (i.e., how many recolors are needed).
- Return the minimum number of such recolors.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for the prefix sum vector.

Input:
- Number of test cases t
- For each test case: n (length of string), k (target consecutive black cells)
- String s of length n containing only 'W' and 'B'

Output:
- Minimum number of white cells to recolor to black for a segment of k consecutive 'B's
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k; // Read input values
    std::string s;
    std::cin >> s; // Read the string

    // Build prefix sum array to count black cells up to each index
    std::vector<long> v(n, 0);
    for (long p = 0; p < n; p++) {
      v[p] = (s[p] == 'W') + (p > 0 ? v[p - 1] : 0); // Prefix sum calculation
    }

    // Initialize result with number of white cells in first window of size k
    long res(v[k - 1]);

    // Slide the window and find minimum number of whites in any window
    for (long p = k; p < n; p++) {
      long cur = v[p] - v[p - k]; // Number of whites in current window of size k
      res = (res < cur) ? res : cur; // Update minimum
    }

    std::cout << res << std::endl; // Output the result
  }
}


// https://github.com/VaHiX/codeForces/